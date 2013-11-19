#ifndef TURNSPECIFIEDDEGREESCOMMAND_H
#define TURNSPECIFIEDDEGREESCOMMAND_H

#include "../CommandBase.h"
#include "ProcessVisionCommand.h"

/**
 *
 *
 * @author speterson
 */
class TurnSpecifiedDegreesCommand: public CommandBase {
private:
	float startingAngle;
	float goalAngle;
	float degreesToTurn;
	bool finished;
	
	ProcessVisionCommand *m_vision;
public:
	TurnSpecifiedDegreesCommand(float degreesToTurn);
	TurnSpecifiedDegreesCommand(ProcessVisionCommand *processVision);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
