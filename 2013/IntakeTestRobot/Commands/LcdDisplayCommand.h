#ifndef LCDDISPLAYCOMMAND_H
#define LCDDISPLAYCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class LcdDisplayCommand: public CommandBase {
public:
	LcdDisplayCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
