#ifndef VISION_SUBSYSTEM_H
#define VISION_SUBSYSTEM_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "Math.h"
//#include "algorithm"
#include "Vision/RGBImage.h"
#include "Vision/BinaryImage.h"

//Camera Constants for the calc of distance
#define X_IMAGE_RES 640 // Can be 160 320 640
#define Y_IMAGE_RES 480
#define VIEW_ANGLE 43.5 //Axis M1011 FOV = 43.5 or 48 for Axis 206
#define PI 3.141592653

//Score limits for target id
#define RECTANGULARITY_LIMIT 60
#define ASPECT_RATIO_LIMIT 75
#define X_EDGE_LIMIT 40
#define Y_EDGE_LIMIT 60

//Minimum area of particles to be considered
#define AREA_MINIMUM 500

//Edge profile constants used for hollowness score calculation
#define XMAXSIZE 24
#define XMINSIZE 24
#define YMAXSIZE 24
#define YMINSIZE 48
const double xMax[XMAXSIZE] = { 1, 1, 1, 1, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, 1, 1, 1, 1 };
const double xMin[XMINSIZE] = {.4, .6, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1, 0.6, 0};
const double yMax[YMAXSIZE] = {1, 1, 1, 1, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, .5, 1, 1, 1, 1};
const double yMin[YMINSIZE] = {.4, .6, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .05, .6, 0};

//Color Threshold Values
#define THRESHOLD_HUE_MIN 93
#define THRESHOLD_HUE_MAX 117
#define THRESHOLD_SATURATION_MIN 153
#define THRESHOLD_SATURATION_MAX 255
#define THRESHOLD_VALUE_MIN 100
#define THRESHOLD_VALUE_MAX 255


#define TOP_TARGET 0
#define MIDDLE_TARGET 1
#define BOTTOM_TARGET 2

const float cameraHight = 0.0;
//#define CAMERAHIGHT
const float targetHight[3] = {
		0,	//Top Target Hight
		0,	//Middle Target Hight
		0,	//Bottom taget Hight
};
const float targetHalfWidth[3] = {
		0,	//Width of Top target
		0,	//Width of MIddle target
		0,	//Width of Bottom Target
};

/**
 *
 *
 * @author Ryan Sjostrand
 */

struct Scores {
		double rectangularity;
		double aspectRatioInner;
		double aspectRatioOuter;
		double xEdge;
		double yEdge;
};

class VisionSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilitie
	bool IsImageProcessed;
	
	Scores *scores;
	
	//const char* cameraIP = "10.30.81.12";
	
	bool targetVisable[3];
	double targetDistances[3];
	float targetAzimuth[3];
	float targetPitch[3];
	
	double targetPositionX[3];
	double targetPositionY[3];

	double computeDistance(BinaryImage *image, ParticleAnalysisReport *report, bool outer);
	double scoreAspectRatio(BinaryImage *image, ParticleAnalysisReport *report, bool outer);
	bool scoreCompare(Scores scores, bool outer);
	double scoreRectangularity(ParticleAnalysisReport *report);
	double scoreXEdge(BinaryImage *image, ParticleAnalysisReport *report);
	double scoreYEdge(BinaryImage *image, ParticleAnalysisReport *report);
	double VisionSubsystem::targetPosition(int targetID, bool XOrY);
	float inverseTan(float opposite, float adjacent);
	
public:
	VisionSubsystem();
	void InitDefaultCommand();
	bool IsTargetVisible(int targetID);
	double GetTargetDistance(int targetID);
	float GetTargetAzimuth(int targetID);
	float GetTargetPitch(int targetID);
	float GetTargetPosition(int targetID, bool XOrY);
	void ProcessImage();
	bool IsImageReady();

};

#endif /* VISION_SUBSYSTEM_H */
