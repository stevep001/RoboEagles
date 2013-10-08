#ifndef AUTODONOTHINGCOMMAND_H
#define AUTODONOTHINGCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class AutoDoNothingCommand: public CommandBase {
public:
	AutoDoNothingCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
