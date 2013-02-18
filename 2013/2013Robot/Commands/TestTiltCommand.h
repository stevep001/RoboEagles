#ifndef TESTTILTCOMMAND_H
#define TESTTILTCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class TestTiltCommand: public CommandBase {
private:
	float power;
public:
	TestTiltCommand(float power);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
