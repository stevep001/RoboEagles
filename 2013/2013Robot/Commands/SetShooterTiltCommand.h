#ifndef SETSHOOTERTILTCOMMAND_H
#define SETSHOOTERTILTCOMMAND_H

#include "../CommandBase.h"
#include "ProcessVisionCommand.h"

/**
 *
 *
 * @author speterson
 */
class SetShooterTiltCommand: public CommandBase {
private:
	float angle;
	
	ProcessVisionCommand *m_vision;
public:
	SetShooterTiltCommand(float angle);
	SetShooterTiltCommand(ProcessVisionCommand *processVision);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
