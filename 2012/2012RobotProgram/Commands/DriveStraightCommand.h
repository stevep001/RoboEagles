#ifndef DRIVESTRAIGHTCOMMAND_H
#define DRIVESTRAIGHTCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class DriveStraightCommand: public CommandBase {
private:
	float time;
	float speed;
	Timer *drivingTimer;
public:
	DriveStraightCommand(float time, float speed);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
