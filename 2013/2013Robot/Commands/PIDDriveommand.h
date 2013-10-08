#ifndef PIDDRIVEOMMAND_H
#define PIDDRIVEOMMAND_H

//Need to firgure out the following values
#define TEETH_DRIVE 24
#define TEETH_WHEEL 32
#define DIAMETER_WHEEL 8
#define TICKS_ENCODER 1024

#include "../CommandBase.h"

/**
 *
 *
 * @author robotics
 */
class PIDDriveommand: public CommandBase {
private:
	PIDController *leftController;
	PIDController *rightController;
	double distance;
public:
	PIDDriveommand(float inches);
	PIDDriveommand(int feet, int inches, bool forward);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	void cleanUp();
};

#endif
