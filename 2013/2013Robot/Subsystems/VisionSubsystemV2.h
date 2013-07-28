#ifndef VISIONV2_SUBSYSTEM_H
#define VISIONV2_SUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "Vision/BinaryImage.h"
#include "Vision/ColorImage.h"
#include "Vision/AxisCamera.h"
#include "Vision/RGBImage.h"
#include "Vision2009/VisionAPI.h"
#include <string>
//#include <math.h>
#include <cmath>
#include "WPILib.h"

#define VISIONSUBSYSTEM_V2_DEBUG 1

#define TARGET_HIGH 0
#define TARGET_MIDDLE 1
#define TARGET_MIDDLE_TWO 2

/*
 * Threshold Values
 */
#define HUE_MIN	93
#define HUE_MAX	120
#define SATURATION_MIN	153
#define SATURATION_MAX	255
#define VALUE_MIN	100
#define VALUE_MAX	255

//Particle Filter Criteria Area minimum
#define AREA_MINIMUM 500


/*
 * Scoreing Values for X & Y
 */
#define XMAXSIZE 24
#define XMINSIZE 24
#define YMAXSIZE 24
#define YMINSIZE 48

/*
 * Stuff for the score compare function
 */
#define RECTANGULARITY_LIMIT 60
#define ASPECT_RATIO_LIMIT 75
#define X_EDGE_LIMIT 40
#define Y_EDGE_LIMIT 60

/*
 * Values for distance
 */
#define X_IMAGE_RES 640 // Can be 160 320 640
/*
 * Datasheet FOV Angles
 * Axis M1011 FOV = 43.5 
 * Axis 206 = 48
 * 
 * Could be: 42.6
 */
#define VIEW_ANGLE_V2 42.6
#define Y_IMAGE_RES 480
#define PI_V2 3.14159265359

/**
 *
 *
 * @author Ryan Sjostrand
 */

const double xMaxV2[XMAXSIZE] = { 1, 1, 1, 1, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, 1, 1, 1, 1 };
const double xMinV2[XMINSIZE] = {.4, .6, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, 0.6, 0};
const double yMaxV2[YMAXSIZE] = {1, 1, 1, 1, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, 1, 1, 1, 1};
const double yMinV2[YMINSIZE] = {.4, .6, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .6, 0};

struct ScoresV2 {
		double rectangularity;
		double aspectRatioInner;
		double aspectRatioOuter;
		double xEdge;
		double yEdge;
};

class VisionSubsystemV2: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	
	//Variables
	ScoresV2 *scores;
	
	bool isImageProcessed;
	
	bool isHighTargetVisable;
	double highTargetPositionX;
	double highTargetPositionY;
	int highTargetCenterOfMassX;
	int highTargetCenterOfMassY;
	double highTargetDistance;
	double highAzimuth;
	
	bool isMiddleTargetVisable;
	double middleTargetPositionX;
	double middleTargetPositionY;
	int middleTargetCenterOfMassX;
	int middleTargetCenterOfMassY;
	double middleTargetDistance;
	double middleAzimuth;
	
	bool isThereSecondMiddleTarget;
	bool isMiddleTargetVisable2;
	double middleTargetPositionX2;
	double middleTargetPositionY2;
	int middleTargetCenterOfMassX2;
	int middleTargetCenterOfMassY2;
	double middleTargetDistance2;
	double middleAzimuth2;

	//Functions
	HSLImage *getCameraImage();
	HSLImage *getImageFromcRio();
	
	BinaryImage *thresholdImage(Threshold &threshold, HSLImage *image);
	BinaryImage* convexHullImage(BinaryImage* image);
	BinaryImage *filterImage(BinaryImage *image, ParticleFilterCriteria2 *criteria);
	vector<ParticleAnalysisReport> *particleAnalysisReportOfImage(BinaryImage *image);
	
	double scoreRectangularity(ParticleAnalysisReport *report);
	double scoreAspectRatio(BinaryImage *image, ParticleAnalysisReport *report, bool outer);
	double scoreXEdge(BinaryImage *image, ParticleAnalysisReport *report);
	double scoreYEdge(BinaryImage *image, ParticleAnalysisReport *report);
	bool scoreCompare(ScoresV2 scores, bool outer);
	void scoreImage(vector<ParticleAnalysisReport> *reports, BinaryImage *filteredImage, BinaryImage *thresholdedImage);
	
	void getTargetStatsOut(ParticleAnalysisReport *report, int targetID, BinaryImage *image);
	void zeroOutStats();
	double computeTargetDistance(BinaryImage *image, ParticleAnalysisReport *report, bool outer);
	double computeTargetAzimuth(BinaryImage *image, ParticleAnalysisReport *report, bool highTarget, double targetDistance);
	
	void processImage(HSLImage *image);
	
	double tanDegress(double degress);
	double inverseTan(double ratio);
	
	void toSmartDashDistance(int targetID, double distance);
	void toSmartDashAzimuth(int targetID, double Azimuth);
	void toSmartDashIsTagetThere(int targetID, bool isThere);
	void statsToSmartDash();
	
public:
	VisionSubsystemV2();
	void InitDefaultCommand();
	
	void ProcessCameraImage();
	void ProcesscRIOImage();
	
	bool IsImageProcessed();
	
	
	bool IsHighTargetVisable();
	double GetHighTargetDistance();
	double GetHighTargetAzimuth();
	
	bool IsMiddleTargetVisable();
	double GetMiddleTargetDistance();
	double GetMiddleTargetAzimuth();
	
	bool IsSecondMiddleTargetVisable();
	double GetSecondMiddleTargetDistance();
	double GetSecondMiddleTargetAzimuth();
	
};

#endif
