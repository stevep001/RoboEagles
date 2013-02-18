#ifndef SHOOTERTILTSUPERVISORCOMMAND_H
#define SHOOTERTILTSUPERVISORCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class ShooterTiltSupervisorCommand: public CommandBase {
private:
	PIDController *controller;
	void Cleanup();
	Timer *initializationTimer;
	
public:
	ShooterTiltSupervisorCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
