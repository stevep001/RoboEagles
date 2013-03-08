#ifndef DRIVEFORWARDCOMMAND_H
#define DRIVEFORWARDCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class DriveForwardCommand: public CommandBase {
private:
	int distanceInInches;
	Timer *timer;
	void Stop();
public:
	DriveForwardCommand(int distanceInInches);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
