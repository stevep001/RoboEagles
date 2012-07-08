#ifndef BALLLOADERAUTOMATEDCOMMAND_H
#define BALLLOADERAUTOMATEDCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class BallLoaderAutomatedCommand: public CommandBase {
private:
	bool lastBallState;
public:
	BallLoaderAutomatedCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
