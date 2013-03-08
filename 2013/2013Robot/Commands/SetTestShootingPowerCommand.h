#ifndef SETTESTSHOOTINGPOWERCOMMAND_H
#define SETTESTSHOOTINGPOWERCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class SetTestShootingPowerCommand: public CommandBase {
public:
	SetTestShootingPowerCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
