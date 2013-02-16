#ifndef PIZZA_BOX_SUBSYSTEM_H
#define PIZZA_BOX_SUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"


class PizzaBoxSubsystem: public Subsystem {
private:
	Jaguar *pizzaBoxMotor;
	Jaguar *frisbeeEjectMotor;
	
	void MoveUp();
	void MoveDown();

	int FrisbeeCount;
	int PizzaBoxPosition;
	int TempPBPos;
	
	// This tracks the intermediate state while we are moving from
	// place to place.
	int intermediateState;
	enum PizzaBoxState {
		LoadPosition1,
		LoadPosition2,
		LoadPosition3,
		LoadPosition4,
		FirePosition1,
		FirePosition2,
		FirePosition3,
		FirePosition4,
		Unknown,
		TopPosition,
	};
	PizzaBoxState currentState;
	
public:
	PizzaBoxSubsystem();
	void InitDefaultCommand();
	void MoveTop();  // here for testing but not necessarily use
	void MoveBottom();
	
	bool StartMoveNextLoadingPosition();
	void MoveToNextLoadingPosition();
	void StartMoveFirstLoadingPosition();
	void MoveFirstLoadingPosition();
	bool CanMoveNextLoadingPosition();
	
	void StartMoveFirstFiringPosition();
	void MoveFirstFiringPosition();
	bool StartMoveNextFiringPosition();
	void MoveNextFiringPosition();
	bool CanMoveNextFiringPosition();
	
	void Stop();
	
	bool IsAtTop();
	bool IsAtBottom();
	bool IsBoxFull();
	bool IsInFiringPosition();
	bool IsInLoadingPosition();
	bool SwitchLower();
	bool SwitchUpper();

};

#endif
