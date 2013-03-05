#ifndef STOWPANCOMMAND_H
#define STOWPANCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class StowPanCommand: public CommandBase {
public:
	StowPanCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
