#ifndef DRIVEFORWARDTOFLOORTRANSITIONCOMMAND_H
#define DRIVEFORWARDTOFLOORTRANSITIONCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class DriveForwardToFloorTransitionCommand: public CommandBase {
private:
	bool startingSensorState;
	
public:
	DriveForwardToFloorTransitionCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
