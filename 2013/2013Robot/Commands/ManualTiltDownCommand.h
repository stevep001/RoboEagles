#ifndef MANUALTILTDOWNCOMMAND_H
#define MANUALTILTDOWNCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class ManualTiltDownCommand: public CommandBase {
public:
	ManualTiltDownCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
