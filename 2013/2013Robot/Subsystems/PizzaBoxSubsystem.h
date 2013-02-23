#ifndef PIZZA_BOX_SUBSYSTEM_H
#define PIZZA_BOX_SUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "SensorSubsystem.h"
#include "LEDSubsystem.h"
#include "WPILib.h"


#define MAX_FRISBEES	(4)

class PizzaBoxSubsystem: public Subsystem {
public:
	enum PizzaBoxState {
		LoadingPosition,
		FiringPosition,
		Unknown,
		MovingToNextLoadingPosition,
		MovingToNextFiringPosition,
	};

private:
	SpeedController *pizzaBoxMotor;
	SensorSubsystem *sensorSubsystem;
	LEDSubsystem *ledSubsystem;
	
	int currentPosition;
	PizzaBoxState currentState;
	
public:
	PizzaBoxSubsystem(SensorSubsystem *sensorSubsystem, LEDSubsystem *ledSubsystem);
	void InitDefaultCommand();
	void MoveTop();  // here for testing but not necessarily use
	void MoveBottom();
	
	// These are used by clients
	bool IsInLoadingPosition();
	bool IsInFiringPosition();
	bool FiringSoon();

	void MoveFirstLoadingPosition();
	void MoveNextLoadingPosition();
	void MoveFirstFiringPosition();
	void MoveNextFiringPosition();
	
	// These methods are used by the supervisory command to control the box.
	
	PizzaBoxState GetCurrentState();
	void SetCurrentState(PizzaBoxState newState);
	
	int GetCurrentPosition();
	void SetCurrentPosition(int newPosition);
	
	bool CanMoveNextLoadingPosition();
	bool CanMoveNextFiringPosition();
	
	void Stop();
	
	bool IsAtTopLimit();
	bool IsAtBottomLimit();

	bool IsLoadingSwitchOn();
	bool IsFiringSwitchOn();

	void MoveUp();
	void MoveDown();
};

#endif
