#ifndef SENSORDISPLAYCOMMAND_H
#define SENSORDISPLAYCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class SensorDisplayCommand: public CommandBase {
public:
	SensorDisplayCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
