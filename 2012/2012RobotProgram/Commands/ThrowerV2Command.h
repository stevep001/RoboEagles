#ifndef THROWERV2COMMAND_H
#define THROWERV2COMMAND_H

#include "../CommandBase.h"


/**
 *
 *
 * @author speterson
 */
class ThrowerV2Command: public CommandBase {
private:
	Timer *throwSolenoidTimer;
	float throwTime;
	bool useThrowerSetting;
	bool finished;
	bool retracting;
	void Init(float throwTime);
public:
	ThrowerV2Command();
	ThrowerV2Command(float throwTime);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
