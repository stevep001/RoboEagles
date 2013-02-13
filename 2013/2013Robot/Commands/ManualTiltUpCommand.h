#ifndef MANUALTILTUPCOMMAND_H
#define MANUALTILTUPCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class ManualTiltUpCommand: public CommandBase {
public:
	ManualTiltUpCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
