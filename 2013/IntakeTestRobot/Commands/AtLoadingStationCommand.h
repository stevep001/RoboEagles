#ifndef ATLOADINGSTATIONCOMMAND_H
#define ATLOADINGSTATIONCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class AtLoadingStationCommand: public CommandBase {
public:
	AtLoadingStationCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
