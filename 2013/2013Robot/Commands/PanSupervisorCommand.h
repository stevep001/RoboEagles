#ifndef PANSUPERVISORCOMMAND_H
#define PANSUPERVISORCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class PanSupervisorCommand: public CommandBase {
public:
	PanSupervisorCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
