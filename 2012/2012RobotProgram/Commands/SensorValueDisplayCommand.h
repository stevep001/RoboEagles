#ifndef SENSORVALUEDISPLAYCOMMAND_H
#define SENSORVALUEDISPLAYCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class SensorValueDisplayCommand: public CommandBase {
public:
	SensorValueDisplayCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
