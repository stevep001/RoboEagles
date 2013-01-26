#ifndef POSITIONHOLDINGCOMMAND_H
#define POSITIONHOLDINGCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class PositionHoldingCommand: public CommandBase {
public:
	PositionHoldingCommand();
	~PositionHoldingCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	PIDController *controller;
};

#endif
