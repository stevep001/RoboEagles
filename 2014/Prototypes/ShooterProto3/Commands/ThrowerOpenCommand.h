#ifndef THROWERFORWARDCOMMAND_H
#define THROWERFORWARDCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class ThrowerOpenCommand: public CommandBase {
public:
	ThrowerOpenCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
