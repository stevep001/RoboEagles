#ifndef PIZZA_BOX_SUBSYSTEM_H
#define PIZZA_BOX_SUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"


class PizzaBoxSubsystem: public Subsystem {
private:
	Jaguar *pizzaBoxMotor;
	DigitalInput *topLimitSwitch;
	DigitalInput *botLimitSwitch;
	DigitalInput *upperLimitSwitch;
	DigitalInput *lowerLimitSwitch;
	
	void MoveUp();
	void MoveDown();
	
	int state;
	
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	PizzaBoxSubsystem();
	void InitDefaultCommand();
	void MoveTop();  // here for testing but not necessarily use
	void MoveBottom();
	
	void StartLoadIndex();
	void LoadIndex();
	
	void FireIndex();
	
	void StartMoveFiring();
	void MoveFiringPosition();
	void Stop();
	void SetNumberOfFrisbees(int numberOfFrisbees);
	bool IsAtTop();
	bool IsAtBottom();
	bool IsBoxFull();
	bool IsInFiringPosition();
	bool IsInLoadingPosition();
	bool SwitchLower();
	bool SwitchUpper();

	int FrisbeeCount;
	int PizzaBoxPosition;
	int TempPBPos;
};

#endif
