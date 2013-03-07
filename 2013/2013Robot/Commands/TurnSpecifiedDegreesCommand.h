#ifndef TURNSPECIFIEDDEGREESCOMMAND_H
#define TURNSPECIFIEDDEGREESCOMMAND_H

#include "../CommandBase.h"

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
	
public:
	TurnSpecifiedDegreesCommand(float degreesToTurn);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
