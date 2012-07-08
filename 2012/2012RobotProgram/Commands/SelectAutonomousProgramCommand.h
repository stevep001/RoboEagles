#ifndef SELECTAUTONOMOUSPROGRAMCOMMAND_H
#define SELECTAUTONOMOUSPROGRAMCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class SelectAutonomousProgramCommand: public CommandBase {
public:
	SelectAutonomousProgramCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
