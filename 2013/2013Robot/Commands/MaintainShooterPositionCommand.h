#ifndef MAINTAINSHOOTERPOSITIONCOMMAND_H
#define MAINTAINSHOOTERPOSITIONCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class MaintainShooterPositionCommand: public CommandBase {
public:
	MaintainShooterPositionCommand(float angle);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	PIDController *pidController;
	float angle;
};

#endif
