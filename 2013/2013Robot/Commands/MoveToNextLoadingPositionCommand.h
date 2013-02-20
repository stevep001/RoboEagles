#ifndef MOVETONEXTLOADINGPOSITIONCOMMAND_H
#define MOVETONEXTLOADINGPOSITIONCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class MoveToNextLoadingPositionCommand: public CommandBase {
public:
	MoveToNextLoadingPositionCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
