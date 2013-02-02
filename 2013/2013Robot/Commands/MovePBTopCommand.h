#ifndef MOVE_PB_TOP_COMMAND_H
#define MOVE_PB_TOP_COMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class MovePBTopCommand: public CommandBase {
public:
	MovePBTopCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
