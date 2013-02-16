#ifndef TESTVISIONCOMMAND_H
#define TESTVISIONCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class TestVisionCommand: public CommandBase {
private:
	void PrintTargetValues(int targetId);
public:
	TestVisionCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
