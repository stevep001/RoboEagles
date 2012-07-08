#ifndef INCREASETHROWINGPOWERCOMMAND_H
#define INCREASETHROWINGPOWERCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class ChangeThrowingPowerCommand: public CommandBase {
private:
	int amountToChange;
public:
	ChangeThrowingPowerCommand(int change);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
