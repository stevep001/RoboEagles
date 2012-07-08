#ifndef WAITFORBALLINTHROWERCOMMAND_H
#define WAITFORBALLINTHROWERCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class WaitForBallInThrowerCommand: public CommandBase {
private:
	bool finished;
public:
	WaitForBallInThrowerCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
