#include "VisionSubsystemV2.h"
#include "Vision/AxisCamera.h"
#include <cmath>
#include "../Robotmap.h"

VisionSubsystemV2::VisionSubsystemV2() : Subsystem("VisionSubsystemV2") {
}
    
void VisionSubsystemV2::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

/*
 * Private Functions
 */

HSLImage *VisionSubsystemV2::getCameraImage() {
	AxisCamera &camera = AxisCamera::GetInstance("10.30.81.12");
	printf("[VisionSubsystemV2] (getCameraImage) Getting Image from camera\n");
	return camera.GetImage();
}

HSLImage *VisionSubsystemV2::getImageFromcRio() {
	return new HSLImage("/testImage.jpg");
}

BinaryImage *VisionSubsystemV2::thresholdImage(Threshold &threshold, HSLImage *image) {
	printf("[VisionSubsystemV2] (thresholdImage) Thresholding Image with %d, %d, %d, %d, %d, %d\n", 
			threshold.plane1Low,
			threshold.plane1High,
			threshold.plane2Low,
			threshold.plane2High,
			threshold.plane3Low,
			threshold.plane3High);
	BinaryImage *thresHoldedImage = image->ThresholdHSV(threshold);
	return thresHoldedImage;
}

BinaryImage *VisionSubsystemV2::convexHullImage(BinaryImage *image){
	printf("[VisionSubsystemV2] (convexHullImage) COnvex Hulling image\n");
	return image->ConvexHull(false);
}

BinaryImage *VisionSubsystemV2::filterImage(BinaryImage *image, ParticleFilterCriteria2 *criteria) {
	printf("[VisionSubsystemV2] (filterImage) Filtering image with the ParticleFilterCriteria\n");
	return image->ParticleFilter(criteria, 1);
}

vector<ParticleAnalysisReport> *VisionSubsystemV2::particleAnalysisReportOfImage(BinaryImage *image) {
	printf("[VisionSubsystemV2] (particleAnalysisReportOfImage) Gettting Particle report from Image\n");
	return image->GetOrderedParticleAnalysisReports();
}

double VisionSubsystemV2::scoreRectangularity(ParticleAnalysisReport *report){
	printf("[VisionSubsystemV2] (scoreRectangularity) Scoring rectangle\n");
	if(report->boundingRect.width*report->boundingRect.height != 0) {
		double score = 100*report->particleArea/(report->boundingRect.width*report->boundingRect.height);
		printf("[VisionSubsystemV2] (scoreRectangularity) Score of rectangle is %f\n", score);
		return score;
	} else {
		printf("[VisionSubsystemV2] (scoreRectangularity) Not a rectangle with the score the of 0\n");
		return 0;
	}
}

double VisionSubsystemV2::scoreAspectRatio(BinaryImage *image, ParticleAnalysisReport *report, bool outer) {
	double	rectLong,
			rectShort,
			idealAspectRatio,
			aspectRatio;
	if (outer) {
		idealAspectRatio = (62/29);
	} else {
		idealAspectRatio = (62/20);
	}
	printf("[VisionSubsystemV2] (scoreAspectRatio) Using the aspect ratio of %f to score with\n", idealAspectRatio);
	
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &rectShort);
	
	if (report->boundingRect.width > report->boundingRect.height) {
		aspectRatio = 100*(1 - fabs((1 - ((rectLong / rectShort) / idealAspectRatio))));
	} else {
		aspectRatio = 100*(1 - fabs((1 - ((rectShort / rectLong) / idealAspectRatio))));
	}
	double score = (max(0.0, min(aspectRatio, 1000.00)));
	printf("[VisionSubsystemV2] (scoreAspectRatio) The score is %f\n", score);
	return score;
}

double VisionSubsystemV2::scoreXEdge(BinaryImage *image, ParticleAnalysisReport *report) {
	double total = 0;
	LinearAverages *averages = imaqLinearAverages2(image->GetImaqImage(), IMAQ_COLUMN_AVERAGES, report->boundingRect);
	
	for(int i = 0; i < (averages->columnCount); i++) {
		if (xMinV2[i*(XMINSIZE - 1) / averages->columnCount] < averages->columnAverages[i] && averages->columnAverages[i] < xMaxV2[i*(XMAXSIZE - 1) / averages->columnCount]) {
			total++;
		}
	}
	total = 100*total/(averages->columnCount);
	imaqDispose(averages);
	printf("[VisionSubsystemV2] (scoreXEdge) The score of the X-edge is %f\n", total);
	return total;
}

double VisionSubsystemV2::scoreYEdge(BinaryImage *image, ParticleAnalysisReport *report) {
	double total = 0;
	LinearAverages *averages = imaqLinearAverages2(image->GetImaqImage(), IMAQ_ROW_AVERAGES, report->boundingRect);
	
	for(int i=0; i < (averages->rowCount); i++){
			if(yMinV2[i*(YMINSIZE-1)/averages->rowCount] < averages->rowAverages[i] 
			   && averages->rowAverages[i] < yMaxV2[i*(YMAXSIZE-1)/averages->rowCount]){
				total++;
			}
		}
		total = 100*total/(averages->rowCount);		//convert to score 0-100
		imaqDispose(averages);						//let IMAQ dispose of the averages struct
		printf("[VisionSubsystemV2] (scoreYEdge) The score of the Y-edge is %f\n", total);
	
		return total;
}

bool VisionSubsystemV2::scoreCompare(ScoresV2 scores, bool outer) {
	bool isTarget = true;
	isTarget &= scores.rectangularity > RECTANGULARITY_LIMIT;
	if (outer) {
		isTarget &= scores.aspectRatioOuter > ASPECT_RATIO_LIMIT;
	} else {
		isTarget &= scores.aspectRatioInner > ASPECT_RATIO_LIMIT;
	}
	isTarget &= scores.xEdge > X_EDGE_LIMIT;
	isTarget &= scores.yEdge > Y_EDGE_LIMIT;
	
	return isTarget;
}

double VisionSubsystemV2::computeTargetDistance(BinaryImage *image, ParticleAnalysisReport *report, bool outer) {
	double rectShort, height, targetHeight;
	
	printf("[VisionSubsystemV2] (computeDistance) Image Hight: %d, Image Width: %d\n", image->GetHeight(), image->GetWidth());
	
	if (outer) {
		//Middle
		targetHeight = (29.0 / 12.0);
		printf("[VisionSubsystemV2] (computeDistance) using middle target %f\n", targetHeight);
	} else {
		//High
		targetHeight = 1.666666;
		printf("[VisionSubsystemV2] (computeDistance) using top target height %f\n", targetHeight);
	}
	
	//imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &rectShort);
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE_FERET, &rectShort);
	printf("[VisionSubsystemV2] (computeDistance) imaq rectangle short side is %f\n", rectShort);
	
	double repoertedOfBoundingRect = report->boundingRect.height;
	printf("[VisionSubsystemV2] (computeDistance) Bounding rectangle heigth %f\n", repoertedOfBoundingRect);
	
	height = min(rectShort, repoertedOfBoundingRect);
	printf("[VisionSubsystemV2] (computeDistance) The Height being used is %f\n", height);
	
	double tangent = VisionSubsystemV2::tanDegress(VIEW_ANGLE_V2 / 2);
	printf("[VisionSubsystemV2] (computeDistance) tanget of %f is %f\n", (VIEW_ANGLE_V2 / 2), tangent);
	//double distance = ((((targetHeight / Y_IMAGE_RES) / height ) / 2) / tangent);
	
	double FOV = (targetHeight * Y_IMAGE_RES) / height;
	printf("[VisionSubsystemV2] (computeDistance) Field of view is %f\n", FOV);
	
	double distance = (FOV / 2)/ tangent;
	printf("[VisionSubsystemV2] (computeDistance) Distance is %f\n", distance);
	
	return distance;
}

double VisionSubsystemV2::computeTargetAzimuth(BinaryImage *image, ParticleAnalysisReport *report, bool highTarget, double targetDistance) {
	double targetWidthPixelImaq;
	double targetWidthFeet;
	
	if (highTarget) {
		//This is the width in feet of the high target with tape
		targetWidthFeet = (31.0 / 6.0);
	} else {
		//Need to find middle target width with tape
		targetWidthFeet = (62.0 / 12.0);
	}
	printf("[VisionSubsystemV2] (computeTargetAzimuth) The target width in feet is %f\n", targetWidthFeet);
	
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &targetWidthPixelImaq);
	printf("[VisionSubsystemV2] (computeTargetAzimuth) The imaq pixel width is %f\n", targetWidthPixelImaq);
	
	double targetWidthPixelBoundingRect = report->boundingRect.width;
	printf("[VisionSubsystemV2] (computeTargetAzimuth) The Bounding rectangle width is %f\n", targetWidthPixelBoundingRect);
	
	double targetWidthPixel = min(targetWidthPixelBoundingRect, targetWidthPixelBoundingRect);
	printf("[VisionSubsystemV2] (computeTargetAzimuth) The target width being used is %f\n", targetWidthPixel);
	
	double fov = (targetWidthFeet * image->GetWidth()) / targetWidthPixel;
	printf("[VisionSubsystemV2] (computeTargetAzimuth) The horizontal field of view is %f\n", fov);
	
	double prePreTan = ((report->center_mass_x - (image->GetWidth() / 2)) * (fov / 2)) / image->GetWidth();
	printf("[VisionSubsystemV2] (computeTargetAzimuth) the distance from teh center in feet is %f\n", prePreTan);
	
	double preTan = prePreTan / targetDistance;
	printf("[VisionSubsystemV2] (computeTargetAzimuth) The value before tan is %f\n", preTan);
	
	double azimuth = atan(preTan) * (180.0 / PI_V2);
	printf("[VisionSubsystemV2] (computeTargetAzimuth) the azimuth is %f\n", azimuth);
	
	return azimuth;
}

void VisionSubsystemV2::zeroOutStats(){
	 this->isHighTargetVisable = false;
	 this->highTargetPositionX = 0.0;
	 this->highTargetPositionY = 0.0;
	 this->highTargetCenterOfMassX = 0;
	 this->highTargetCenterOfMassY = 0;
	 this->highTargetDistance = 0.0;
	 this->highAzimuth = 0.0;
	
	 this->isMiddleTargetVisable = false;
	 this->middleTargetPositionX = 0.0;
	 this->middleTargetPositionY = 0.0;
	 this->middleTargetCenterOfMassX = 0;
	 this->middleTargetCenterOfMassY = 0;
	 this->middleTargetDistance = 0.0;
	 this->middleAzimuth = 0.0;
	
	 this->isThereSecondMiddleTarget = false;
	 this->isMiddleTargetVisable2 = false;
	 this->middleTargetPositionX2 = 0.0;
	 this->middleTargetPositionY2 = 0.0;
	 this->middleTargetCenterOfMassX2 = 0;
	 this->middleTargetCenterOfMassY2 = 0;
	 this->middleTargetDistance2 = 0.0;
	 this-> middleAzimuth2 = 0.0;
}

void VisionSubsystemV2::getTargetStatsOut(ParticleAnalysisReport *report, int targetID, BinaryImage *image) {
	if (targetID == TARGET_HIGH) {
		printf("[VisionSubsystemV2] (getTargetStatsOut) Getting stats out for High target\n");
		this->isHighTargetVisable = true;
		this->highTargetCenterOfMassX = report->center_mass_x;
		this->highTargetCenterOfMassY = report->center_mass_y;
		
		this->highTargetDistance = VisionSubsystemV2::computeTargetDistance(image, report, false);
		this->highAzimuth = VisionSubsystemV2::computeTargetAzimuth(image, report, true, this->highTargetDistance);
		
	} else if (targetID == TARGET_MIDDLE) {
		if (this->isThereSecondMiddleTarget == true) {
			printf("[VisionSubsystemV2] (getTargetStatsOut) Getting stats out for Second middle target\n");
			this->isMiddleTargetVisable2 = true;
			this->middleTargetCenterOfMassX2 = report->center_mass_x;
			this->middleTargetCenterOfMassY2 = report->center_mass_y;
			
			this->middleTargetDistance2 = VisionSubsystemV2::computeTargetDistance(image, report, true);
			this->middleAzimuth2 = VisionSubsystemV2::computeTargetAzimuth(image, report, false, this->middleTargetDistance2);
		} else {
			printf("[VisionSubsystemV2] (getTargetStatsOut) Getting stats out for Middle target\n");
			this->isThereSecondMiddleTarget = true;
			this->isMiddleTargetVisable = true;
			this->middleTargetCenterOfMassX = report->center_mass_x;
			this->middleTargetCenterOfMassY = report->center_mass_y;
			
			this->middleTargetDistance = VisionSubsystemV2::computeTargetDistance(image, report, true);
			this->middleAzimuth = VisionSubsystemV2::computeTargetAzimuth(image, report, false, this->middleTargetDistance);
		}
	}
}

void VisionSubsystemV2::scoreImage(vector<ParticleAnalysisReport> *reports, BinaryImage *filteredImage, BinaryImage *thresholdedImage) {
	printf("[VisionSubsystemV2] (scoreImage) Number of found particles found : %d\n", reports->size());
	VisionSubsystemV2::zeroOutStats();
	if (reports->size() != 0) {
		for (unsigned i = 0; i < reports->size(); i++) {
			ParticleAnalysisReport *report = &(reports->at(i));
			scores[i].rectangularity = VisionSubsystemV2::scoreRectangularity(report);
			scores[i].aspectRatioOuter = VisionSubsystemV2::scoreAspectRatio(filteredImage, report, true);
			scores[i].aspectRatioInner = VisionSubsystemV2::scoreAspectRatio(filteredImage, report, false);
			scores[i].xEdge = VisionSubsystemV2::scoreXEdge(thresholdedImage, report);
			scores[i].yEdge = VisionSubsystemV2::scoreYEdge(thresholdedImage, report);
			
			if (scoreCompare(scores[i], false)) {
				VisionSubsystemV2::getTargetStatsOut(report, TARGET_HIGH, thresholdedImage);
				
				printf("[VisionSubsystemV2] (scoreImage) Hight target Found Partice:%d Distance:%f\n", i, this->highTargetDistance);
				printf("[VisionSubsystemV2] (scoreImage) Witdth:%d, Hight:%d\n", report->boundingRect.width, report->boundingRect.height);
			} else if (scoreCompare(scores[i], true)) {
				VisionSubsystemV2::getTargetStatsOut(report, TARGET_MIDDLE, thresholdedImage);
				printf("[VisionSubsystemV2] (scoreImage) Middle target Found Partice:%d Distance:%f\n", i, this->middleTargetDistance);
				printf("[VisionSubsystemV2] (scoreImage) Witdth:%d, Hight:%d\n", report->boundingRect.width, report->boundingRect.height);
			} else {
				/*
				 * No particles are goals
				 */
				printf("[VisionSubsystemV2] (scoreImage) No target Found Particel:%d \n", i);;
			}
		}
	} else {
		/*
		 * No targets found
		 */
		printf("[VisionSubsystemV2] (scoreImage) The particles found are not targets\n");
	}
	
}

double VisionSubsystemV2::tanDegress(double degress) {
	double radians = degress * (PI_V2 / 180); 
	return tan(radians);
}


double VisionSubsystemV2::inverseTan(double ratio) {
	return atan(ratio) * (180 / PI_V2);
}

void VisionSubsystemV2::toSmartDashDistance(int targetID, double distance) {
	if (targetID == TARGET_HIGH) {
		SmartDashboard::PutNumber("Vision High target distance", distance);
	} else if (targetID == TARGET_MIDDLE) {
		SmartDashboard::PutNumber("Vision Middle Target Distance", distance);
	} else if (targetID == TARGET_MIDDLE_TWO) {
		SmartDashboard::PutNumber("Vison Second Middle target distance", distance);
	}
}

void VisionSubsystemV2::toSmartDashAzimuth(int targetID, double Azimuth) {
	if (targetID == TARGET_HIGH) {
		SmartDashboard::PutNumber("Vision High target Azimuth", Azimuth);
	} else if (targetID == TARGET_MIDDLE) {
		SmartDashboard::PutNumber("Vision Middle target", Azimuth);
	} else if (targetID == TARGET_MIDDLE_TWO) {
		SmartDashboard::PutNumber("Vision Second middle target", Azimuth);
	}
}

void VisionSubsystemV2::toSmartDashIsTagetThere(int targetID, bool isThere) {
	if (targetID == TARGET_HIGH) {
		SmartDashboard::PutBoolean("Vision Is High Target There", isThere);
	} else if (targetID == TARGET_MIDDLE) {
		SmartDashboard::PutBoolean("Vision Is Middle target there", isThere);
	} else if (targetID == TARGET_MIDDLE_TWO) {
		SmartDashboard::PutBoolean("Vision Is Second MIddle target there", isThere);
	}
}

void VisionSubsystemV2::statsToSmartDash() {
	VisionSubsystemV2::toSmartDashDistance(TARGET_HIGH, this->highTargetDistance);
	VisionSubsystemV2::toSmartDashDistance(TARGET_MIDDLE, this->middleTargetDistance);
	VisionSubsystemV2::toSmartDashDistance(TARGET_MIDDLE_TWO, this->middleTargetDistance2);
	
	VisionSubsystemV2::toSmartDashAzimuth(TARGET_HIGH, this->highAzimuth);
	VisionSubsystemV2::toSmartDashAzimuth(TARGET_MIDDLE, this->middleAzimuth);
	VisionSubsystemV2::toSmartDashAzimuth(TARGET_MIDDLE_TWO, this->middleAzimuth2);
	
	VisionSubsystemV2::toSmartDashIsTagetThere(TARGET_HIGH, this->isHighTargetVisable);
	VisionSubsystemV2::toSmartDashIsTagetThere(TARGET_MIDDLE, this->isMiddleTargetVisable);
	VisionSubsystemV2::toSmartDashIsTagetThere(TARGET_MIDDLE_TWO, this->isMiddleTargetVisable2);
}

void VisionSubsystemV2::processImage(HSLImage *image) {


		
	/*Threshold threshold(HUE_MIN,
						HUE_MAX, 
						SATURATION_MIN, 
						SATURATION_MAX, 
						VALUE_MIN, 
						VALUE_MAX);
	*/
	
	//Old Threshold
	//Threshold threshold(95, 118, 145, 255, 127, 174); 
	Threshold   threshold(71, 167, 107, 255, 69, 114);
	
	//BinaryImage *thresholdedImage = VisionSubsystemV2::thresholdImage(threshold, image);
	BinaryImage *thresholdedImage = image->ThresholdHSL(threshold);
	//thresholdedImage->Write("/images/threshold.bmp");
	
	BinaryImage *convexHulledImage = VisionSubsystemV2::convexHullImage(thresholdedImage);

	ParticleFilterCriteria2 criteria[] = {
			{IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false}
	};
		
	BinaryImage *filteredImage = VisionSubsystemV2::filterImage(convexHulledImage, criteria);

	vector<ParticleAnalysisReport> *reports = VisionSubsystemV2::particleAnalysisReportOfImage(filteredImage);
		
	scores = new ScoresV2[reports->size()];
		
	VisionSubsystemV2::scoreImage(reports, filteredImage, thresholdedImage);
		
		
	delete filteredImage;
	delete convexHulledImage;
	delete thresholdedImage;
	delete image;
	
	delete scores;
	delete reports;
		

}


/*
 * Public members
 */
void VisionSubsystemV2::ProcessCameraImage() {
	this->isImageProcessed = false;
	HSLImage *cameraImage;
	cameraImage = VisionSubsystemV2::getCameraImage();
	VisionSubsystemV2::processImage(cameraImage);
	cameraImage = NULL;
	this->isImageProcessed = true;
}

void VisionSubsystemV2::ProcesscRIOImage() {
	this->isImageProcessed = false;
	HSLImage *cRIOImage;
	cRIOImage = VisionSubsystemV2::getImageFromcRio();
	VisionSubsystemV2::processImage(cRIOImage);
	cRIOImage = NULL;
	this->isImageProcessed = true;
}

bool VisionSubsystemV2::IsImageProcessed() {
	return this->isImageProcessed;
}

bool VisionSubsystemV2::IsHighTargetVisable() {
	return this->isHighTargetVisable;
}

double VisionSubsystemV2::GetHighTargetDistance() {
	return this->highTargetDistance;
}

double VisionSubsystemV2::GetHighTargetAzimuth() {
	return this->highAzimuth;
}

bool VisionSubsystemV2::IsMiddleTargetVisable() {
	return this->isMiddleTargetVisable;
}

double VisionSubsystemV2::GetMiddleTargetDistance() {
	return this->middleTargetDistance;
}

double VisionSubsystemV2::GetMiddleTargetAzimuth() {
	return this->middleAzimuth;
}

bool VisionSubsystemV2::IsSecondMiddleTargetVisable(){
	return this->isMiddleTargetVisable2;
}

double VisionSubsystemV2::GetSecondMiddleTargetDistance() {
	return this->middleTargetDistance2;
}

double VisionSubsystemV2::GetSecondMiddleTargetAzimuth() {
	return this->middleAzimuth2;
}
