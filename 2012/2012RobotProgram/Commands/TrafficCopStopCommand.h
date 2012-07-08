#ifndef TRAFFICCOPSTOPCOMMAND_H
#define TRAFFICCOPSTOPCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class TrafficCopStopCommand: public CommandBase {
public:
	TrafficCopStopCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
