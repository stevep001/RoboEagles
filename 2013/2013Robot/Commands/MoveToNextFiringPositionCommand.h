#ifndef MOVETONEXTFIRINGPOSITIONCOMMAND_H
#define MOVETONEXTFIRINGPOSITIONCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class MoveToNextFiringPositionCommand: public CommandBase {
public:
	MoveToNextFiringPositionCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
