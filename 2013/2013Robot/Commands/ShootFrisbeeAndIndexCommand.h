#ifndef SHOOTFRISBEEANDINDEXCOMMAND_H
#define SHOOTFRISBEEANDINDEXCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class ShootFrisbeeAndIndexCommand: public CommandBase {
private:
	enum CommandState {
		Starting,
		StartFiring,
		WaitingForKickerToComplete,
		MovingToNextFiringPosition,
		Done
	};
	CommandState state;
	
public:
	ShootFrisbeeAndIndexCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
