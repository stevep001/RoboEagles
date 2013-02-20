#ifndef LIFTPANCOMMAND_H
#define LIFTPANCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class LiftPanCommand: public CommandBase {
private:
	bool up;
public:
	LiftPanCommand(bool up);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
