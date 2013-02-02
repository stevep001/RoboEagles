#ifndef MOVE_PB_BOTTOM_COMMAND_H
#define MOVE_PB_BOTTOM_COMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class MovePBBottomCommand: public CommandBase {
public:
	MovePBBottomCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
