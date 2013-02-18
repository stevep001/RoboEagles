#include "PizzaBoxSupervisorCommand.h"

PizzaBoxSupervisorCommand::PizzaBoxSupervisorCommand() {
	Requires(pizzaBoxSubsystem);
}

void PizzaBoxSupervisorCommand::Initialize() {
	// If the frisbee shooter is at the top position, we assume it is full.
	// Otherwise it's empty.

	if (pizzaBoxSubsystem->IsAtTopLimit())
	{
		printf("Pizza box at top limit, moving into first firing position\n");
		pizzaBoxSubsystem->SetCurrentState(PizzaBoxSubsystem::MovingToNextFiringPosition);
		pizzaBoxSubsystem->SetCurrentPosition(0);
		this->intermediateState = InPosition;
	}
	else
	{
		printf("Pizza box not at top limit, moving to first loading position\n");
		pizzaBoxSubsystem->SetCurrentState(PizzaBoxSubsystem::MovingToNextLoadingPosition);
		pizzaBoxSubsystem->SetCurrentPosition(0);
		this->intermediateState = InPosition;
	}	
}

void PizzaBoxSupervisorCommand::Execute() {
	this->UpdateDashboard(pizzaBoxSubsystem->GetCurrentState());
	
	switch (pizzaBoxSubsystem->GetCurrentState())
	{
		case PizzaBoxSubsystem::FiringPosition:
		case PizzaBoxSubsystem::LoadingPosition:
			// do nothing
			this->intermediateState = InPosition;
			break;
		case PizzaBoxSubsystem::MovingToNextLoadingPosition:
			switch (this->intermediateState)
			{
				case InPosition:
					this->StartMoveToNextLoadingPosition();
					break;
				case MovingToLoadingSwitchOff:
					if (!sensorSubsystem->GetPizzaLowerLimitSwitch())
					{
						this->intermediateState = MovingToLoadingSwitchOn;
					}
					pizzaBoxSubsystem->MoveUp();
					break;
				case MovingToLoadingSwitchOn:
					if (sensorSubsystem->GetPizzaLowerLimitSwitch())
					{
						pizzaBoxSubsystem->Stop();
						this->intermediateState = InPosition;
						this->pizzaBoxSubsystem->SetCurrentState(PizzaBoxSubsystem::LoadingPosition);
						this->pizzaBoxSubsystem->SetCurrentPosition(pizzaBoxSubsystem->GetCurrentPosition() + 1);
					}
					else
					{
						pizzaBoxSubsystem->MoveUp();
					}
				default:
					// TODO Can probably ignore other states.
					break;
			}
			break;
		case PizzaBoxSubsystem::MovingToNextFiringPosition:
			switch (this->intermediateState)
			{
				case InPosition:
					this->StartMoveToNextFirePosition();
					break;
				case MovingToFireSwitchOff:
					if (!sensorSubsystem->GetPizzaUpperLimitSwitch())
					{
						this->intermediateState = MovingToFireSwitchOn;
					}
					pizzaBoxSubsystem->MoveUp();
					break;
				case MovingToFireSwitchOn:
					if (sensorSubsystem->GetPizzaUpperLimitSwitch())
					{
						pizzaBoxSubsystem->Stop();
						this->intermediateState = InPosition;
						pizzaBoxSubsystem->SetCurrentState(PizzaBoxSubsystem::FiringPosition);
						pizzaBoxSubsystem->SetCurrentPosition(pizzaBoxSubsystem->GetCurrentPosition() + 1);
					}
					else
					{
						pizzaBoxSubsystem->MoveUp();
					}
				default:
					// TODO Can probably ignore other states.
					break;
			}
			break;
		case PizzaBoxSubsystem::Unknown:
			pizzaBoxSubsystem->SetCurrentPosition(0);
			this->StartMoveToNextFirePosition();
			break;
	}
}
void PizzaBoxSupervisorCommand::UpdateDashboard(PizzaBoxSubsystem::PizzaBoxState state)
{
	char *message;
	switch (state)
	{
	case PizzaBoxSubsystem::FiringPosition:
		message = "Firing Position";
		break;
	case PizzaBoxSubsystem::LoadingPosition:
		message = "Loading Position";
		break;
	case PizzaBoxSubsystem::MovingToNextFiringPosition:
		message = "Moving to next firing position";
		break;
	case PizzaBoxSubsystem::MovingToNextLoadingPosition:
		message = "Moving to next loading position";
		break;
	case PizzaBoxSubsystem::Unknown:
		message = "Position unknown";
		break;
	}
	SmartDashboard::PutString("Pizza box state", message);
	SmartDashboard::PutNumber("Pizza box positiion", pizzaBoxSubsystem->GetCurrentPosition());
}

void PizzaBoxSupervisorCommand::StartMoveToNextLoadingPosition()
{
	// This gets the loading process going
	if (pizzaBoxSubsystem->GetCurrentPosition() == 0)
	{
		if (pizzaBoxSubsystem->IsAtBottomLimit()) {
			if (pizzaBoxSubsystem->IsLoadingSwitchOn())
			{
				// We are done, don't need to load anything.
				
				pizzaBoxSubsystem->Stop();
				pizzaBoxSubsystem->SetCurrentPosition(1);
				pizzaBoxSubsystem->SetCurrentState(PizzaBoxSubsystem::LoadingPosition);
				return;
			}
			else
			{
				this->intermediateState = MovingToLoadingSwitchOn;
				pizzaBoxSubsystem->MoveUp();
				printf("At bottom, moving to first loading position\n");
			}
		}
		else
		{
			this->intermediateState = MovingToBottom;
			pizzaBoxSubsystem->MoveDown();
			printf("Moving to bottom\n");
		}
	} 
	else
	{
		printf("Moving to next loading position\n");
		if (pizzaBoxSubsystem->GetCurrentPosition() == MAX_FRISBEES)
		{
			printf("Error -- pizza box is already in loading position 4\n");
			return;
		}

		if (sensorSubsystem->GetPizzaLowerLimitSwitch())
		{
			this->intermediateState = MovingToLoadingSwitchOff;
		}
		else
		{
			// Perhaps the box has been nudged a bit and it is below the limit switch.
			// A crappy way to recover but we'll just wait for the lower switch to come on.
			
			// Maybe we'd be better off giving up here.
			
			printf("StartLoadIndex but lower switch is off.");
			this->intermediateState = MovingToLoadingSwitchOn;
		}
		pizzaBoxSubsystem->MoveUp();
		
		return;
	}
	
}

void PizzaBoxSupervisorCommand::StartMoveToNextFirePosition()
{
	if (pizzaBoxSubsystem->GetCurrentPosition() == 0)
	{
		if (pizzaBoxSubsystem->IsAtTopLimit()) {
			if (pizzaBoxSubsystem->IsFiringSwitchOn())
			{
				// We are done, don't need to load anything.
				
				pizzaBoxSubsystem->Stop();
				pizzaBoxSubsystem->SetCurrentPosition(1);
				pizzaBoxSubsystem->SetCurrentState(PizzaBoxSubsystem::FiringPosition);
				return;
			}
			else
			{
				this->intermediateState = MovingToFireSwitchOn;
				pizzaBoxSubsystem->MoveDown();
				printf("At top, moving to first firing position\n");
			}
		}
		else
		{
			this->intermediateState = MovingToTop;
			pizzaBoxSubsystem->MoveUp();
			printf("Moving to top\n");
		}
	} 
	else
	{
		printf("Moving to next firing position\n");
		if (pizzaBoxSubsystem->GetCurrentPosition() == MAX_FRISBEES)
		{
			printf("Error -- pizza box is already in firing position 4\n");
			return;
		}

		if (sensorSubsystem->GetPizzaUpperLimitSwitch())
		{
			this->intermediateState = MovingToFireSwitchOff;
		}
		else
		{
			// Perhaps the box has been nudged a bit and it is below the limit switch.
			// A crappy way to recover but we'll just wait for the lower switch to come on.
			
			// Maybe we'd be better off giving up here.
			
			printf("StartLoadIndex but lower switch is off.");
			this->intermediateState = MovingToFireSwitchOn;
		}
		pizzaBoxSubsystem->MoveDown();
		
		return;
	}
	
}

// Make this return true when this Command no longer needs to run execute()
bool PizzaBoxSupervisorCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void PizzaBoxSupervisorCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PizzaBoxSupervisorCommand::Interrupted() {
}

//
//void PizzaBoxSupervisorCommand::MoveFirstLoadingPosition()
//{
//	printf("MoveFirstLoadingPosition: ");
//	if (this->intermediateState == WAITING_FOR_BOTTOM_LIMIT_SWITCH_ON)
//	{
//		if (this->IsAtBottom())
//		{
//			this->intermediateState = WAITING_FOR_LOWER_SWITCH_ON;
//			this->MoveUp();
//			printf("Reached bottom, starting move up.\n");
//		}
//		else
//		{
//			this->MoveDown();
//		}
//	}
//	else if (this->intermediateState == WAITING_FOR_LOWER_SWITCH_ON)
//	{
//		if (this->SwitchLower())
//		{
//			printf("Saw lower switch, stopping.\n");
//			this->Stop();
//			this->PizzaBoxPosition = FIRE_POSITION_1;
//		}
//		else
//		{
//			this->MoveUp();
//		}
//	}
//	else
//	{
//		printf("Unexpected intermediate state: %d", this->intermediateState);
//		this->Stop();
//	}
//}
//
//bool PizzaBoxSupervisorCommand::StartMoveNextLoadingPosition()
//{
//	printf("StartMoveNextLoadingPosition: ");
//	if (this->PizzaBoxPosition == LOAD_POSITION_4)
//	{
//		printf("Error -- pizza box is already in loading position 4\n");
//		// Set this so that the box doesn't move.
//		this->intermediateState = WAITING_FOR_LOWER_SWITCH_ON;
//		return false;
//	}
//
//	printf("Starting move to next loading position\n");
//	if (this->SwitchLower())
//	{
//		this->intermediateState = WAITING_FOR_LOWER_SWITCH_OFF;
//	} else {
//		// Perhaps the box has been nudged a bit and it is below the limit switch.
//		// A crappy way to recover but we'll just wait for the lower switch to come on.
//		
//		// Maybe we'd be better off giving up here.
//		
//		printf("StartLoadIndex but lower switch is off.");
//		this->intermediateState = WAITING_FOR_LOWER_SWITCH_ON;
//	}
//	
//	pizzaBoxMotor->Set(MOTOR_SPEED_UP);\
//	return true;
//}
//
//// Called repeated from calling command until we're in position
//void PizzaBoxSupervisorCommand::MoveToNextLoadingPosition() {
//	printf("MoveToNextLoadingPosition: ");
//	if (this->intermediateState == WAITING_FOR_LOWER_SWITCH_OFF)
//	{
//		if (!this->SwitchLower())
//		{
//			this->intermediateState = WAITING_FOR_LOWER_SWITCH_ON;
//		}
//		this->MoveUp();
//	}
//	else if (this->intermediateState == WAITING_FOR_LOWER_SWITCH_ON)
//	{
//		// Ahh, yes.  We're there.
//		if (this->SwitchLower())
//		{
//			this->Stop();
//			switch (this->PizzaBoxPosition)
//			{
//				case LOAD_POSITION_1:
//					this->PizzaBoxPosition = LOAD_POSITION_2;
//					break;
//				case LOAD_POSITION_2:
//					this->PizzaBoxPosition = LOAD_POSITION_3;
//					break;
//				case LOAD_POSITION_3:
//					this->PizzaBoxPosition = LOAD_POSITION_4;
//					break;
//				default:
//					printf("unknown ending state %d\n", this->PizzaBoxPosition);
//					break;
//			}
//		}
//	} else {
//		printf("Unknown intermediate state %d\n", this->intermediateState);
//		this->Stop();
//	}
//}
//
//// Moving to the first firing position moves through two states.
//// First, we move to the top position.
//// Then we move down until we reach the first firing position.
//void PizzaBoxSupervisorCommand::StartMoveFirstFiringPosition()
//{
//	printf("StartMoveFirstFiringPosition: ");
//	if (!this->IsAtTop())
//	{
//		this->intermediateState = WAITING_FOR_TOP_LIMIT_SWITCH_ON;
//		this->MoveUp();
//		printf("Moving to top position\n");
//	}
//	else
//	{
//		this->intermediateState = WAITING_FOR_UPPER_LIMIT_SWITCH_ON;
//		this->MoveDown();
//		printf("At top, moving down to first shooting position\n");
//	}
//}
//
//void PizzaBoxSupervisorCommand::MoveFirstFiringPosition()
//{
//	printf("MoveFirstFiringPosition");
//	if (this->intermediateState == WAITING_FOR_TOP_LIMIT_SWITCH_ON)
//	{
//		if (this->IsAtTop())
//		{
//			this->intermediateState = WAITING_FOR_UPPER_LIMIT_SWITCH_ON;
//			this->MoveDown();
//			printf("Reached top, starting move down.\n");
//		}
//		else
//		{
//			this->MoveUp();
//		}
//	}
//	else if (this->intermediateState == WAITING_FOR_UPPER_LIMIT_SWITCH_ON)
//	{
//		if (this->SwitchUpper())
//		{
//			printf("Saw upper switch, stopping.\n");
//			this->Stop();
//			this->PizzaBoxPosition = FIRE_POSITION_1;
//		}
//		else
//		{
//			this->MoveDown();
//		}
//	}
//	else
//	{
//		printf("Unexpected intermediate state: %d", this->intermediateState);
//		this->Stop();
//	}
//}
//
//bool PizzaBoxSupervisorCommand::StartMoveNextFiringPosition()
//{
//	switch (this->PizzaBoxPosition)
//	{
//		case FIRE_POSITION_1:
//		case FIRE_POSITION_2:
//		case FIRE_POSITION_3:
//			if (this->SwitchUpper())
//			{
//				this->intermediateState = WAITING_FOR_UPPER_LIMIT_SWITCH_OFF;
//			}
//			else
//			{
//				printf("StartMoveNextFiringPosition: not in a known position\n");
//				this->intermediateState = WAITING_FOR_LOWER_SWITCH_ON;
//			}
//			this->MoveDown();
//			return true;
//			break;
//		default:
//			printf("StartMoveNextFiringPosition: can't move there from %d\n", this->PizzaBoxPosition);
//			return false;
//			break;
//	}
//}
//
//void PizzaBoxSupervisorCommand::MoveNextFiringPosition()
//{
//	if (this->intermediateState == WAITING_FOR_UPPER_LIMIT_SWITCH_OFF)
//	{
//		if (!this->SwitchUpper())
//		{
//			this->intermediateState = WAITING_FOR_UPPER_LIMIT_SWITCH_ON;
//		}
//		this->MoveDown();
//	} 
//	else if (this->intermediateState == WAITING_FOR_UPPER_LIMIT_SWITCH_ON)
//	{
//		if (this->SwitchUpper())
//		{
//			this->Stop();
//		}
//	}
//	else
//	{
//		printf("MoveNextFiringPosition: Unnown intermediate state: %d\n", this->intermediateState);
//	}
//}
