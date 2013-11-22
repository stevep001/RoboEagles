#include "VisionSubsystemV2.h"
#include <cmath>

#ifndef _WIN32
#include "../Robotmap.h"
#include "Vision/AxisCamera.h"
#endif

VisionSubsystemV2::VisionSubsystemV2() : Subsystem("VisionSubsystemV2") {
}
    
void VisionSubsystemV2::InitDefaultCommand() {
}

/*
 * Private Functions
 */


HSLImage *VisionSubsystemV2::getCameraImage() {
	HSLImage *cameraImage = NULL;
	cameraImage = new HSLImage();
	#ifndef _WIN32
	AxisCamera &camera = AxisCamera::GetInstance("10.30.81.12");
	
	int cameraError = camera.GetImage(cameraImage);
	#else
	int cameraError = 0;
	#endif
	
	if(cameraError == 0) {
		printf("[VisionSubsystemV2] (getCameraImage) The axis cam protected image buffer is null, returning NULL\n");
		return NULL;
	}
	return cameraImage;

	printf("[VisionSubsystemV2] (getCameraImage) Getting Image from camera\n");
}


HSLImage *VisionSubsystemV2::getImageFromcRio() {
	return new HSLImage("Y:\\testImage.jpeg.jpg");
}

HSLImage *VisionSubsystemV2::getImageFromFileSystem(const char *filename) {
	return new HSLImage(filename);
}

BinaryImage *VisionSubsystemV2::thresholdImage(Threshold &threshold, HSLImage *image) {
	printf("[VisionSubsystemV2] (thresholdImage) Thresholding Image with %d, %d, %d, %d, %d, %d\n", 
			threshold.plane1Low,
			threshold.plane1High,
			threshold.plane2Low,
			threshold.plane2High,
			threshold.plane3Low,
			threshold.plane3High);
	BinaryImage *thresHoldedImage = image->ThresholdHSL(threshold);
	return thresHoldedImage;
}

BinaryImage *VisionSubsystemV2::convexHullImage(BinaryImage *image){
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (convexHullImage) COnvex Hulling image\n");
	#endif
	return image->ConvexHull(false);
}

BinaryImage *VisionSubsystemV2::filterImage(BinaryImage *image, ParticleFilterCriteria2 *criteria) {
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (filterImage) Filtering image with the ParticleFilterCriteria\n");
	#endif
	return image->ParticleFilter(criteria, 1);
}

vector<ParticleAnalysisReport> *VisionSubsystemV2::particleAnalysisReportOfImage(BinaryImage *image) {
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (particleAnalysisReportOfImage) Gettting Particle report from Image\n");
	#endif
	return image->GetOrderedParticleAnalysisReports();
}

double VisionSubsystemV2::scoreRectangularity(ParticleAnalysisReport *report){
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (scoreRectangularity) Scoring rectangle\n");
	#endif	
	if(report->boundingRect.width*report->boundingRect.height != 0) {
		double score = 100*report->particleArea/(report->boundingRect.width*report->boundingRect.height);
		#ifndef VISION_DEBUG_PRINTF_ENABLE
		printf("[VisionSubsystemV2] (scoreRectangularity) Score of rectangle is %f\n", score);
		#endif
		return score;
	} else {
		#ifndef VISION_DEBUG_PRINTF_ENABLE
		printf("[VisionSubsystemV2] (scoreRectangularity) Not a rectangle with the score the of 0\n");
		#endif
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
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (scoreAspectRatio) Using the aspect ratio of %f to score with\n", idealAspectRatio);
	#endif
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &rectShort);
	
	if (report->boundingRect.width > report->boundingRect.height) {
		aspectRatio = 100*(1 - fabs((1 - ((rectLong / rectShort) / idealAspectRatio))));
	} else {
		aspectRatio = 100*(1 - fabs((1 - ((rectShort / rectLong) / idealAspectRatio))));
	}
	double score = (max(0.0, min(aspectRatio, 1000.00)));
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (scoreAspectRatio) The score is %f\n", score);
	#endif
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
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (scoreXEdge) The score of the X-edge is %f\n", total);
	#endif
	return total;
}

double VisionSubsystemV2::scoreYEdge(BinaryImage *image, ParticleAnalysisReport *report) {
	double total = 0;
	LinearAverages *averages = imaqLinearAverages2(image->GetImaqImage(), IMAQ_ROW_AVERAGES, report->boundingRect);
	
	for(int i=0; i < (averages->rowCount); i++){
		if(yMinV2[i*(YMINSIZE-1)/averages->rowCount] < averages->rowAverages[i] && averages->rowAverages[i] < yMaxV2[i*(YMAXSIZE-1)/averages->rowCount]){
				total++;
		}
	}
	total = 100*total/(averages->rowCount);		//convert to score 0-100
	imaqDispose(averages);						//let IMAQ dispose of the averages struct
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (scoreYEdge) The score of the Y-edge is %f\n", total);
	#endif	
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

double VisionSubsystemV2::computeTargetDistance(BinaryImage *image, ParticleAnalysisReport *report, VisionSubsystemV2::Target target) {
	double rectShort, height, targetHeight = -1;
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (computeDistance) Image Hight: %d, Image Width: %d\n", image->GetHeight(), image->GetWidth());
	#endif	
	if(target == High) {
		targetHeight = (20.0 / 12.0);
		#ifndef VISION_DEBUG_PRINTF_ENABLE
		printf("[VisionSubsystemV2] (computeDistance) Using High target height %f\n", targetHeight);
		#endif
	} else if(target == Middle) {
		targetHeight = (29.0 / 12.0);
		#ifndef VISION_DEBUG_PRINTF_ENABLE
		printf("[VisionSubsystemV2] (computeDistance) Using Middle target height %f\n", targetHeight);
		#endif
	} else if(target == Low) {
		targetHeight = (32.0 / 12.0);
		#ifndef VISION_DEBUG_PRINTF_ENABLE
		printf("[VisionSubsystemV2] (computeDistance) Using Low target height %f\n", targetHeight);
		#endif
	}
	
	//imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &rectShort);
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE_FERET, &rectShort);
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (computeDistance) imaq rectangle short side is %f\n", rectShort);
	#endif

	double repoertedOfBoundingRect = report->boundingRect.height;
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (computeDistance) Bounding rectangle heigth %f\n", repoertedOfBoundingRect);
	#endif

	height = min(rectShort, repoertedOfBoundingRect);
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (computeDistance) The Height being used is %f\n", height);
	#endif

	double tangent = VisionSubsystemV2::tanDegress(VIEW_ANGLE_V2 / 2);
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (computeDistance) tanget of %f is %f\n", (VIEW_ANGLE_V2 / 2), tangent);
	#endif
	//double distance = ((((targetHeight / Y_IMAGE_RES) / height ) / 2) / tangent);
	
	double FOV = (targetHeight * Y_IMAGE_RES) / height;
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (computeDistance) Field of view is %f\n", FOV);
	#endif

	double distance = (FOV / 2)/ tangent;
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (computeDistance) Distance is %f\n", distance);
	#endif

	return distance;
}

double VisionSubsystemV2::computeTargetAzimuth(BinaryImage *image, ParticleAnalysisReport *report, Target target, double targetDistance) {
	double targetWidthPixelImaq;
	double targetWidthFeet = -1;
	
	if(target == High) {
		targetWidthFeet = (62.0 / 12.0);
	} else if(target == Middle) {
		targetWidthFeet = (62.0 / 12.0);
	} else if(target == Low) {
		targetWidthFeet = (37.0 / 12.0);
	}
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (computeTargetAzimuth) The target width in feet is %f\n", targetWidthFeet);
	#endif
	
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &targetWidthPixelImaq);
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (computeTargetAzimuth) The imaq pixel width is %f\n", targetWidthPixelImaq);
	#endif

	double targetWidthPixelBoundingRect = report->boundingRect.width;
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (computeTargetAzimuth) The Bounding rectangle width is %f\n", targetWidthPixelBoundingRect);
	#endif

	double targetWidthPixel = min(targetWidthPixelBoundingRect, targetWidthPixelBoundingRect);
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (computeTargetAzimuth) The target width being used is %f\n", targetWidthPixel);
	#endif

	double fov = (targetWidthFeet * image->GetWidth()) / targetWidthPixel;
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (computeTargetAzimuth) The horizontal field of view is %f\n", fov);
	#endif

	double prePreTan = ((report->center_mass_x - (image->GetWidth() / 2)) * (fov / 2)) / image->GetWidth();
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (computeTargetAzimuth) the distance from teh center in feet is %f\n", prePreTan);
	#endif

	double preTan = prePreTan / targetDistance;
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (computeTargetAzimuth) The value before tan is %f\n", preTan);
	#endif

	double azimuth = atan(preTan) * (180.0 / PI_V2);
	#ifndef VISION_DEBUG_PRINTF_ENABLE
	printf("[VisionSubsystemV2] (computeTargetAzimuth) the azimuth is %f\n", azimuth);
	#endif

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

void VisionSubsystemV2::getTargetStatsOut(ParticleAnalysisReport *report, Target target, BinaryImage *image) {
	if (target == High) {
		#ifndef VISION_DEBUG_PRINTF_ENABLE
		printf("[VisionSubsystemV2] (getTargetStatsOut) Getting stats out for High target\n");
		#endif
		this->isHighTargetVisable = true;
		this->highTargetCenterOfMassX = report->center_mass_x;
		this->highTargetCenterOfMassY = report->center_mass_y;
		
		this->highTargetDistance = VisionSubsystemV2::computeTargetDistance(image, report, High);
		this->highAzimuth = VisionSubsystemV2::computeTargetAzimuth(image, report, High, this->highTargetDistance);
		
	} else if (target == Middle) {
		if (this->isThereSecondMiddleTarget == true) {
			#ifndef VISION_DEBUG_PRINTF_ENABLE
			printf("[VisionSubsystemV2] (getTargetStatsOut) Getting stats out for Second middle target\n");
			#endif
			this->isMiddleTargetVisable2 = true;
			this->middleTargetCenterOfMassX2 = report->center_mass_x;
			this->middleTargetCenterOfMassY2 = report->center_mass_y;
			
			this->middleTargetDistance2 = VisionSubsystemV2::computeTargetDistance(image, report, Middle);
			this->middleAzimuth2 = VisionSubsystemV2::computeTargetAzimuth(image, report, Middle, this->middleTargetDistance2);
		} else {
			#ifndef VISION_DEBUG_PRINTF_ENABLE
			printf("[VisionSubsystemV2] (getTargetStatsOut) Getting stats out for Middle target\n");
			#endif
			this->isThereSecondMiddleTarget = true;
			this->isMiddleTargetVisable = true;
			this->middleTargetCenterOfMassX = report->center_mass_x;
			this->middleTargetCenterOfMassY = report->center_mass_y;
			
			this->middleTargetDistance = VisionSubsystemV2::computeTargetDistance(image, report, Middle);
			this->middleAzimuth = VisionSubsystemV2::computeTargetAzimuth(image, report, Middle, this->middleTargetDistance);
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
				VisionSubsystemV2::getTargetStatsOut(report, High, thresholdedImage);
				
				printf("[VisionSubsystemV2] (scoreImage) Hight target Found Partice:%d Distance:%f\n", i, this->highTargetDistance);
				printf("[VisionSubsystemV2] (scoreImage) Witdth:%d, Hight:%d\n", report->boundingRect.width, report->boundingRect.height);
			} else if (scoreCompare(scores[i], true)) {
				VisionSubsystemV2::getTargetStatsOut(report, Middle, thresholdedImage);
				printf("[VisionSubsystemV2] (scoreImage) Middle target Found Partice:%d Distance:%f\n", i, this->middleTargetDistance);
				printf("[VisionSubsystemV2] (scoreImage) Witdth:%d, Hight:%d\n", report->boundingRect.width, report->boundingRect.height);
			} else {
				/*
				 * No particles are goals
				 */
				printf("[VisionSubsystemV2] (scoreImage) Partice:%d is not target\n", i);;
			}
		}
	} else {
		/*
		 * No targets found
		 */
		printf("[VisionSubsystemV2] (scoreImage) None of the Particles are targets\n");
	}
	
}

double VisionSubsystemV2::tanDegress(double degress) {
	double radians = degress * (PI_V2 / 180); 
	return tan(radians);
}


double VisionSubsystemV2::inverseTan(double ratio) {
	return atan(ratio) * (180 / PI_V2);
}

void VisionSubsystemV2::processImage(HSLImage *image) {
	//Threshold threshold(HUE_MIN,
	//					HUE_MAX, 
	//					SATURATION_MIN, 
	//					SATURATION_MAX, 
	//					VALUE_MIN, 
	//					VALUE_MAX);
	//
 
	//Threshold   threshold(95, 255, 193, 255, 90, 186);
	Threshold threshold(95,255,190,255,75,255);

	BinaryImage *thresholdedImage = VisionSubsystemV2::thresholdImage(threshold, image);
	
	BinaryImage *convexHulledImage = VisionSubsystemV2::convexHullImage(thresholdedImage);

	ParticleFilterCriteria2 criteria[] = { {IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false} };
		
	BinaryImage *filteredImage = VisionSubsystemV2::filterImage(convexHulledImage, criteria);

	vector<ParticleAnalysisReport> *reports = VisionSubsystemV2::particleAnalysisReportOfImage(filteredImage);
		
	scores = new ScoresV2[reports->size()];
		
	VisionSubsystemV2::scoreImage(reports, filteredImage, thresholdedImage);
		
	delete filteredImage;
	delete convexHulledImage;
	delete thresholdedImage;
	
	delete scores;
	delete reports;
}

bool VisionSubsystemV2::checkImageForProcessing(HSLImage *image) {
	if(image == NULL) {
		return false;
	}
	if((image->GetHeight() * image->GetWidth()) == 0) {
		return false;
	}
	return true;
}

/*
 * Public members
 */
void VisionSubsystemV2::ProcessCameraImage() {
	this->isImageProcessed = false;
	HSLImage *cameraImage;
	cameraImage = VisionSubsystemV2::getCameraImage();
	
	if(checkImageForProcessing(cameraImage)) {
		#ifndef _WIN32
		VisionSubsystemV2::processImage(cameraImage);
		#endif
	} else {
		printf("[VisionSubsystemV2](ProcessCameraImage) Image Is NULL or is unworkable\n");
	}

	delete cameraImage;
	cameraImage = NULL;
	this->isImageProcessed = true;
}

void VisionSubsystemV2::ProcesscRIOImage() {
	this->isImageProcessed = false;
	HSLImage *cRIOImage;
	cRIOImage = VisionSubsystemV2::getImageFromcRio();
	
	if(checkImageForProcessing(cRIOImage)) {
		VisionSubsystemV2::processImage(cRIOImage);
	} else {
		printf("[VisionSubsystemV2](ProcesscRIOImage) Image did not pass test aborting processing");
	}
	
	delete cRIOImage;
	cRIOImage = NULL;
	this->isImageProcessed = true;
}

void VisionSubsystemV2::ProcessImageFromFileSystem(const char *filename) {
	this->isImageProcessed = false;
	HSLImage *fileSystemImage;
	fileSystemImage = VisionSubsystemV2::getImageFromFileSystem(filename);
	
	if(checkImageForProcessing(fileSystemImage)) {
		VisionSubsystemV2::processImage(fileSystemImage);
	} else {
		printf("[VisionSubsystemV2](ProcessImageFromFileSystem) Image did not pass test aborting processing");
	}
	
	delete fileSystemImage;
	fileSystemImage = NULL;
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
