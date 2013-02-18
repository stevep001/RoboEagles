#ifndef TESTKICKERCOMMAND_H
#define TESTKICKERCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class TestKickerCommand: public CommandBase {
public:
	TestKickerCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
