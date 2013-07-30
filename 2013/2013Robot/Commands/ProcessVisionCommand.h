#ifndef PROCESSVISIONCOMMAND_H
#define PROCESSVISIONCOMMAND_H

#include "../CommandBase.h"

/*
 * Need To figure out the distance
 */

#define TILT_ANGLE_22 3
#define TILT_ANGLE_24 4
#define TILT_ANGLE_26 5
#define TILT_ANGLE_28 6
#define TILT_ANGLE_30 7
#define TILT_ANGLE_32 8
#define TILT_ANGLE_34 10
#define TILT_ANGLE_36 12
#define TILT_ANGLE_38 14
#define TILT_ANGLE_40 16

#define TILT_ANGLE_LOWER_LIMIT 22
#define TILT_ANGLE_HIGH_LIMIT 40
/**
 *
 *
 * @author nowireless
 */
class ProcessVisionCommand: public CommandBase {
private:
	Timer *timer;
	float distance;
	float azimuth;
	float shooterTiltAngle;
	float computeTiltAngle(float distance);
	bool targetsVisable;
public:
	ProcessVisionCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	float GetDistance();
	float GetAzimuth();
	float GetTiltAngle();
	bool AreTargetsVisable();
};

#endif
