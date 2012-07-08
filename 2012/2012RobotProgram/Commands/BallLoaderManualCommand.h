#ifndef BALLLOADERMANUALCOMMAND_H
#define BALLLOADERMANUALCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class BallLoaderManualCommand: public CommandBase {
private:
	bool isFlapDown;
	bool sawFlapToggleButton;
public:
	BallLoaderManualCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
