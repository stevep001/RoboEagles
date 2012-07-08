#ifndef EJECTBALLSCOMMAND_H
#define EJECTBALLSCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class EjectBallsCommand: public CommandBase {
private:
	float timeToEject;
	Timer *timer;
public:
	EjectBallsCommand(float timeToEject);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
