#ifndef RUNINTAKECOMMAND_H
#define RUNINTAKECOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class RunIntakeCommand: public CommandBase {
public:
	RunIntakeCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
