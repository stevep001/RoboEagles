#ifndef KICKERSUPERVISORCOMMAND_H
#define KICKERSUPERVISORCOMMAND_H

#include "../CommandBase.h"


/**
 *
 *
 * @author speterson
 */
class KickerSupervisorCommand: public CommandBase {
private:
	void RunMotor();
	void StopMotor();
public:
	KickerSupervisorCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
