#ifndef FRISBEEPANSUPERVISORCOMMAND_H
#define FRISBEEPANSUPERVISORCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class FrisbeePanSupervisorCommand: public CommandBase {
private:
	//PIDController *controller;
	bool OnTarget(float setpoint, float currentValue, float tolerance);
	int initialCalibrationCount;
	Timer *ingestTimer;
public:
	FrisbeePanSupervisorCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
