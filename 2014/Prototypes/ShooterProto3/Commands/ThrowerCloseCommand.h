#ifndef THROWERBACKWORDCOMMAND_H
#define THROWERBACKWORDCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class ThrowerCloseCommand: public CommandBase {
public:
	ThrowerCloseCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
