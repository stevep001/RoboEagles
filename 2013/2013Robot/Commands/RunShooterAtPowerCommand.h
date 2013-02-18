#ifndef RUNSHOOTERATPOWERCOMMAND_H
#define RUNSHOOTERATPOWERCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class RunShooterAtPowerCommand: public CommandBase {
private:
	float power;
public:
	RunShooterAtPowerCommand(float power);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
