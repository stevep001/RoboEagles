#ifndef AIMDOWNCOMMAND_H
#define AIMDOWNCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class AimDownCommand: public CommandBase {
public:
	AimDownCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
