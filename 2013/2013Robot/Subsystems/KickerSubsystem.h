#ifndef KICKERSUBSYSTEM_H
#define KICKERSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "PizzaBoxSubsystem.h"
#include "SensorSubsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class KickerSubsystem: public Subsystem {
	public:
	enum KickerState {
		/*
		 * We start in this state, so that the command knows to retract the kicker.
		 */
		Initializing,
		/*
		 * This state indicates that the kicker is in the stowed position and is not being
		 * commanded to do anything.
		 */
		Stowed,
		/*
		 * This state indicates that the kicker has been commanded, and is waiting for the limit
		 * switch to turn off.  This occurs early in the cycle when it begins to move but
		 * has not moved far enough for the switch to turn off.
		 */
		KickingWaitingForSwitchOff,
		/*
		 * This state indicates that the kicker has been commanded, and is waiting for the limit
		 * switch to turn on.  This occurs later in the cycle.
		 */
		KickingWaitingForSwitchOn,
		
	};
private:
	SpeedController *kickerMotor;
	KickerState kickerState;
	PizzaBoxSubsystem *pizzaBoxSubsystem;
	SensorSubsystem *sensorSubsystem;
	
public:
	
	KickerSubsystem(PizzaBoxSubsystem *pizzaBoxSubsystem, SensorSubsystem *sensorSubsystem);
	void InitDefaultCommand();
	void SetSpeed(float speed);
	KickerState GetKickerState();
	void SetKickerState(KickerState newState);
	void Kick();
	bool CanKick();
	bool IsStowed();
};
#endif
