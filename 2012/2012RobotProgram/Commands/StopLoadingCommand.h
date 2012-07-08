#ifndef STOPLOADINGCOMMAND_H
#define STOPLOADINGCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class StopLoadingCommand: public CommandBase {
public:
	StopLoadingCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
