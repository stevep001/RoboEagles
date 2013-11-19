#ifndef TURNSPECIFIEDDEGREESPIDCOMMAND_H
#define TURNSPECIFIEDDEGREESPIDCOMMAND_H

#include "../CommandBase.h"
#include "ProcessVisionCommand.h"
//#include "../DrivetrainPIDoutput.h"

/**
 *
 *
 * @author nowireless
 */
class TurnSpecifiedDegreesPIDCommand: public CommandBase, public PIDOutput{
private:
	PIDController *controller;
	void cleanUp();
	float pGain;
	float iGain;
	float dGain;
	float feedforward;
	
	float pidGyroMin;
	float pidGyroMax;
	
	float setPointTolerance;
	
	float setPoint;
public:
	TurnSpecifiedDegreesPIDCommand(float degrees);
	TurnSpecifiedDegreesPIDCommand(ProcessVisionCommand *processVision);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	void PIDWrite(float output);
};

#endif
