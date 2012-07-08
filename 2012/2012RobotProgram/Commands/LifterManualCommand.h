#ifndef LIFTERMANUALCOMMAND_H
#define LIFTERMANUALCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class LifterManualCommand: public CommandBase {
public:
	LifterManualCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
