#ifndef DEPLOYPANCOMMAND_H
#define DEPLOYPANCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class DeployPanCommand: public CommandBase {
public:
	DeployPanCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
