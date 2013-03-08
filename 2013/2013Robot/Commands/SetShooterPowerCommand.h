#ifndef SETSHOOTERPOWERCOMMAND_H
#define SETSHOOTERPOWERCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class SetShooterPowerCommand: public CommandBase {
public:
	SetShooterPowerCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
