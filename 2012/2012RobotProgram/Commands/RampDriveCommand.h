#ifndef RAMPDRIVECOMMAND_H
#define RAMPDRIVECOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class RampDriveCommand: public CommandBase {
public:
	RampDriveCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
