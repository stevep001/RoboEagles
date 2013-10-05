#ifndef SHOOTERSUPERVISORCOMMAND_H
#define SHOOTERSUPERVISORCOMMAND_H

#include "../CommandBase.h"
#include "../RpmSource.h"

class ShooterSupervisorCommand: public CommandBase {
private:
	float m_speed;
public:
	ShooterSupervisorCommand();
	~ShooterSupervisorCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	void Cleanup();
};

#endif
