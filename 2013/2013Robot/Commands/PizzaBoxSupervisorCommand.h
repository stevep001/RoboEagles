#ifndef PIZZABOXSUPERVISORCOMMAND_H
#define PIZZABOXSUPERVISORCOMMAND_H

#include "../CommandBase.h"

// These intermediate states are used to track progress toward the
// next position
#define WAITING_FOR_LOWER_SWITCH_OFF 1
#define WAITING_FOR_LOWER_SWITCH_ON 2
#define WAITING_FOR_TOP_LIMIT_SWITCH_ON 3
#define WAITING_FOR_UPPER_LIMIT_SWITCH_ON 4
#define WAITING_FOR_UPPER_LIMIT_SWITCH_OFF 5
#define WAITING_FOR_BOTTOM_LIMIT_SWITCH_ON 6

/**
 *
 *
 * @author speterson
 */
class PizzaBoxSupervisorCommand: public CommandBase {
private:
	
	void StartMoveToNextLoadingPosition();
	void StartMoveToNextFirePosition();
	void UpdateDashboard(PizzaBoxSubsystem::PizzaBoxState state);
//	
//	bool StartMoveNextLoadingPosition();
//	void MoveToNextLoadingPosition();
//	void StartMoveFirstLoadingPosition();
//	void MoveFirstLoadingPosition();
//	bool CanMoveNextLoadingPosition();
//	
//	void StartMoveFirstFiringPosition();
//	void MoveFirstFiringPosition();
//	bool StartMoveNextFiringPosition();
//	void MoveNextFiringPosition();
//	bool CanMoveNextFiringPosition();
	
	enum IntermediateState {
		MovingToBottom,
		MovingToTop,
		MovingToFireSwitchOff,
		MovingToFireSwitchOn,
		MovingToLoadingSwitchOff,
		MovingToLoadingSwitchOn,
		InPosition,
	};
	IntermediateState intermediateState;

public:
	PizzaBoxSupervisorCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

	bool IsInFiringPosition();
	bool IsInLoadingPosition();
};

#endif
