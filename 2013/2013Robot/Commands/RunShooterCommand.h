#ifndef RUNSHOOTERCOMMAND_H
#define RUNSHOOTERCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class RunShooterCommand: public CommandBase {
private:
	float power;
public:
	RunShooterCommand(float power);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
