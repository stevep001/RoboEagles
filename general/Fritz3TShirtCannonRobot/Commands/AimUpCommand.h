#ifndef FIRECOMMAND_H
#define AIMCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class AimUpCommand: public CommandBase {
public:
	AimUpCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
