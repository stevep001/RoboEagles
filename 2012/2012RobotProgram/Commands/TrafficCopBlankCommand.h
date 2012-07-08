#ifndef TRAFFICCOPBLANKCOMMAND_H
#define TRAFFICCOPBLANKCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class TrafficCopBlankCommand: public CommandBase {
public:
	TrafficCopBlankCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
