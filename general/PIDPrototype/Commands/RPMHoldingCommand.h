#ifndef RPMHOLDINGCOMMAND_H
#define RPMHOLDINGCOMMAND_H

#include "../CommandBase.h"
#include "../RPMSource.h"

class RPMHoldingCommand: public CommandBase {
private:
	PIDController *controller;
	Timer *timer;
	double lastTime;
	INT32 lastCount;
	RPMSource* rpmSource;
	double rpmMaximum;
	double previousSamples[5];
	int sampleCount;
	double GetRPM(double currentCount);
public:
	RPMHoldingCommand();
	~RPMHoldingCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
