#include "VisionSubsystem.h"
#include "../Robotmap.h"
#include "math.h"

/**
 *
 *
 * @author Ryan Sjostrand
 */

VisionSubsystem::VisionSubsystem() : Subsystem("VisionSubsystem") {
}
    
void VisionSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}


// Put methods for controlling this subsystem
// here. Call these from Commands.
void InitDefaultCommand() {
}

bool VisionSubsystem::IsTargetVisible(int targetID) {
	return targetVisable[targetID];
}
double VisionSubsystem::GetTargetDistance(int targetID) {
	return targetDistances[targetID];
}
float VisionSubsystem::GetTargetPitch(int targetID) {
	float ratio = ((VisionSubsystem::targetPosition(targetID, false) + 1) / 2);
	float distance = VisionSubsystem::GetTargetDistance(targetID);
	float hight = ratio * (targetHight[targetID] - cameraHight);
	
	float radian = atan(hight / distance);
	float degree = radian * (180 / PI);
	return degree;
}
float VisionSubsystem::GetTargetAzimuth(int targetID) {
	/*
	 * 
	 * float location = VisionSubsystem::targetPosition(targetID);
	 * if (location <= 0) {
	 *	location * -1;
	 * }
	 */
	return 0.0; //PlaceHolder
}
float  VisionSubsystem::GetTargetPosition(int targetID, bool XOrY) {
	if (XOrY == true) {
		return targetPositionX[targetID];
	} else {
		return targetPositionY[targetID];
	}
}
void VisionSubsystem::ProcessImage() {
	printf("Vision: Starting Vision Subsystem\n");
	///////////////
	// Seting Up //
	///////////////
	
	
		
		targetVisable[TOP_TARGET] = false;
		targetVisable[MIDDLE_TARGET] = false;
		targetVisable[BOTTOM_TARGET] = false;
		
		targetDistances[TOP_TARGET] = 0.0;
		targetDistances[MIDDLE_TARGET] = 0.0;
		targetDistances[BOTTOM_TARGET] = 0.0;
		
		targetPositionX[TOP_TARGET] = 0.0;
		targetPositionY[TOP_TARGET] = 0.0;
		targetPositionX[MIDDLE_TARGET] = 0.0;
		targetPositionY[MIDDLE_TARGET] = 0.0;
		targetPositionX[BOTTOM_TARGET] = 0.0;
		targetPositionY[BOTTOM_TARGET] = 0.0;
	/*
	 * This creates a object with the needed values for the processing 
	 * the image later on, for a certain color. 
	 */
	printf("Vision: Setting the clor threshold values\n");
	Threshold threshold(THRESHOLD_HUE_MIN, 
						THRESHOLD_HUE_MAX, 
						THRESHOLD_SATURATION_MIN, 
						THRESHOLD_SATURATION_MAX, 
						THRESHOLD_VALUE_MIN, 
						THRESHOLD_VALUE_MAX);
	
	ParticleFilterCriteria2 criteria[] = {
			{IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false}
	};
	
	/*
	 * This is the function that sets up the axis camera to get images.
	 * To use the camera on the second port on the cRIO, uncommet the second line below 
	 * with "192.168.0.90" in it.
	 */
	printf("Vision: Setting camera IP to 10.30.81.12/n");
	AxisCamera &camera = AxisCamera::GetInstance("10.30.81.12");
	
	//AxisCamera &camera = AxisCamera::GetInstance("192.168.0.90"); //
	
	// This creates a Color image, then on the second line it fills it with the image from the camera.
	printf("Vision: Creating ColorImage object image\n");
	ColorImage *image;
	
	printf("Vision: Getting the Image from the camera \n");
	image = camera.GetImage();
	
	//////////////////////////////
	// Image processing section //
	//////////////////////////////
	
	//Process the image with the threshold values
	printf("Vision: Filtering the image with threshold values into object thresholdImage\n");
	BinaryImage *thesholdImage = image->ThresholdHSV(threshold);
	
	//This will fill shape that is complete and fill in the inside of siad shape.
	printf("Vision: Filling in the convex shapes into the object of convexHullImage\n");
	BinaryImage *convexHullImage = thesholdImage->ConvexHull(false);
	
	//This will get rid of random particles in the image that are notconcentrated enougth.
	printf("Vision: Filtering image for the unwanted random particles");
	BinaryImage *filteredImage = convexHullImage->ParticleFilter(criteria, 1);
	
	//This creates a report that will be used later to idenify targets
	printf("Vision: Creating the report of the filtered Image\n");
	vector<ParticleAnalysisReport> *reports = filteredImage->GetOrderedParticleAnalysisReports();
	
	//This creates a data stucture that is used to score objects.
	
	scores = new Scores[reports->size()];
	
	for (unsigned i = 0; i < reports->size(); i++) {
		ParticleAnalysisReport *report = &(reports->at(i));
		
		scores[i].rectangularity = scoreRectangularity(report);
		scores[i].aspectRatioOuter = scoreAspectRatio(filteredImage, report, true);
		scores[i].aspectRatioInner = scoreAspectRatio(filteredImage, report, false);
		scores[i].xEdge = scoreXEdge(thesholdImage, report);
		scores[i].yEdge = scoreYEdge(thesholdImage, report);
		
		if(scoreCompare(scores[i], false)) {
			printf("Vision: particle: %d is High Goal  centerX %f  centerY: %f \n", i , report->center_mass_x_normalized, report->center_mass_y_normalized);
			printf("Vision: Distance: %f \n", computeDistance(thesholdImage, report, false));
			
			targetPositionX[TOP_TARGET] = report->center_mass_x;
			targetPositionY[TOP_TARGET] = report->center_mass_y;
			targetDistances[TOP_TARGET] = computeDistance(thesholdImage, report, false);
			targetVisable[TOP_TARGET] = true;
			
			targetPositionX[TOP_TARGET] = targetPosition(TOP_TARGET, true);
			targetPositionY[TOP_TARGET] = targetPosition(TOP_TARGET, false);
			
		} else if (scoreCompare(scores[i], true)){
			printf("Vision: particle: %d is Middle Goal  centerX %f  centerY: %f \n", i , report->center_mass_x_normalized, report->center_mass_y_normalized);
			printf("Vision: Distance: %f \n", computeDistance(thesholdImage, report, true));
			
			
			targetPositionX[MIDDLE_TARGET] = report->center_mass_x;
			targetPositionY[MIDDLE_TARGET] = report->center_mass_y;
			targetDistances[MIDDLE_TARGET] = computeDistance(thesholdImage, report, true);
			targetVisable[MIDDLE_TARGET] = true;
			
			targetPositionX[MIDDLE_TARGET] = targetPosition(MIDDLE_TARGET, true);
			targetPositionY[MIDDLE_TARGET] = targetPosition(MIDDLE_TARGET, false);
		} else {
			printf("Vision: particle %d is not a goal  centerX: %f  centery: %f \n" , i, report->center_mass_x_normalized, report->center_mass_y_normalized);
		}
		printf("Vision: rect: %f  ARinner: %f \n", scores[i].rectangularity, scores[i].aspectRatioInner);
		printf("Vision: ARouter: %f  xEdge: %f  yEdge: %f \n", scores[i].aspectRatioOuter, scores[i].xEdge, scores[i].yEdge);
	}
	//printf("\n");
	printf("Vision: Deleting the object filtered image\n");
	delete filteredImage;
	printf("Vision: Deleting the objectconvexHullImage\n");
	delete convexHullImage;
	printf("Vision: Deleting the object thresholdimage\n");
	delete thesholdImage;
	printf("Vision: Deleting the object image");
	delete image;
	
	delete scores;
	delete reports;
	printf("Vision: Done\n");
}
bool VisionSubsystem::IsImageReady() {
	return IsImageProcessed;
}


//Computes the estimated distance to the target using the hight from the particle form the captured image.
double VisionSubsystem::computeDistance (BinaryImage *image, ParticleAnalysisReport *report, bool outer) {
		double rectShort, height;
		int targetHeight;
		
		imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &rectShort);
		//using the smaller of the estimated rectangle short side and the bounding rectangle height results in better performance
		//on skewed rectangles
		double reportedOfBoundingRect = report->boundingRect.height;
		height = min(reportedOfBoundingRect, rectShort);
		targetHeight = outer ? 29 : 21;
		
		return X_IMAGE_RES * targetHeight / (height * 12 * 2 * tan(VIEW_ANGLE*PI/(180*2)));
	}

double VisionSubsystem::scoreAspectRatio(BinaryImage *image, ParticleAnalysisReport *report, bool outer) {
	double rectLong, rectShort, idealAspectRatio, aspectRatio;
	idealAspectRatio = outer ? (62/29) : (62/20);
	
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &rectShort);
	
	if(report->boundingRect.width > report->boundingRect.height) {
		aspectRatio = 100*(1-fabs((1-((rectLong/rectShort)/idealAspectRatio))));
	} else {
		aspectRatio = 100*(1-fabs((1-((rectShort/rectLong)/idealAspectRatio))));
	}
	return (max(0.0, min(aspectRatio, 1000.00)));
}


bool VisionSubsystem::scoreCompare(Scores scores, bool outer) {
	bool isTarget = true;
		isTarget &= scores.rectangularity > RECTANGULARITY_LIMIT;
 	if(outer){
 		isTarget &= scores.aspectRatioOuter > ASPECT_RATIO_LIMIT;
 	} else {
 		isTarget &= scores.aspectRatioInner > ASPECT_RATIO_LIMIT;
 	}
 	isTarget &= scores.xEdge > X_EDGE_LIMIT;
 	isTarget &= scores.yEdge > Y_EDGE_LIMIT;
 
 		return isTarget;
}


double VisionSubsystem::scoreRectangularity(ParticleAnalysisReport *report) {
	if(report->boundingRect.width*report->boundingRect.height !=0){
		return 100*report->particleArea/(report->boundingRect.width*report->boundingRect.height);
	} else {
		return 0;
	}
}

double VisionSubsystem::scoreXEdge(BinaryImage *image, ParticleAnalysisReport *report) {
	double total = 0;
	LinearAverages *averages = imaqLinearAverages2(image->GetImaqImage(), IMAQ_COLUMN_AVERAGES, report->boundingRect);
	for(int i=0; i < (averages->columnCount); i++) {
		if(xMin[i*(XMINSIZE-1)/averages->columnCount] < averages->columnAverages[i] && averages->columnAverages[i] < xMax[i*(XMAXSIZE-1)/averages->columnCount]) {
			total++;
		}
	}
	total = 100*total/(averages->columnCount);
	imaqDispose(averages);
	return total;
}

double VisionSubsystem::scoreYEdge(BinaryImage *image, ParticleAnalysisReport *report) {
	double total = 0;
	LinearAverages *averages = imaqLinearAverages2(image->GetImaqImage(), IMAQ_ROW_AVERAGES, report->boundingRect);
	for(int i=0; i < (averages->rowCount); i++){
		if(yMin[i*(YMINSIZE-1)/averages->rowCount] < averages->rowAverages[i] 
		   && averages->rowAverages[i] < yMax[i*(YMAXSIZE-1)/averages->rowCount]){
			total++;
		}
	}
	total = 100*total/(averages->rowCount);		//convert to score 0-100
	imaqDispose(averages);						//let IMAQ dispose of the averages struct
	return total;
}

//True For X Fasle For Y
double VisionSubsystem::targetPosition(int targetID, bool XOrY) {
	if (XOrY = true) {
		return ((targetPositionX[targetID] - (X_IMAGE_RES) / 2) / (X_IMAGE_RES / 2));
	} else {
		return ((targetPositionY[targetID] - (Y_IMAGE_RES) / 2) / (Y_IMAGE_RES / 2));
	}
}

float VisionSubsystem::inverseTan(float opposite, float adjacent) {
	return atan(opposite / adjacent) * (180 / PI);
}
