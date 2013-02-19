#ifndef SETSHOOTERTILTCOMMAND_H
#define SETSHOOTERTILTCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class SetShooterTiltCommand: public CommandBase {
private:
	float angle;
public:
	SetShooterTiltCommand(float angle);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
