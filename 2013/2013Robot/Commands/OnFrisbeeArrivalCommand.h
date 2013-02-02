#ifndef ON_FRISBEE_ARRIVAL_COMMAND_H
#define ON_FRISBEE_ARRIVAL_COMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */

class OnFrisbeeArrivalCommand: public CommandBase {
private:
	bool prepareForFiring;
public:
	OnFrisbeeArrivalCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};


#endif
