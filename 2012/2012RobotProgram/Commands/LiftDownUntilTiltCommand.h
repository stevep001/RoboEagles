#ifndef LIFTDOWNUNTILTILTCOMMAND_H
#define LIFTDOWNUNTILTILTCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class LiftDownUntilTiltCommand: public CommandBase {
private:
	bool finished;
	float initialPitchAngle;
public:
	LiftDownUntilTiltCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
