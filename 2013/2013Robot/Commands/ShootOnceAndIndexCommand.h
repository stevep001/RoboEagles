#ifndef SHOOTONCEANDINDEX_COMMAND_H
#define SHOOTONCEANDINDEX_COMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Ryan Sjostrand
 */

class ShootOnceAndIndexCommand: public CommandBase {
private:
	enum CommandState {
		Starting,
		StartFiring,
		WaitingForKickerToFinish,
		MovingToNextFiringPosition,
		PostFiring,
		PostFireMovingToNextFiringPosition,
		PostFireMovingToFirstLoadingPosition,
		Done
	};
	
	CommandState state;
	
public:
	ShootOnceAndIndexCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
