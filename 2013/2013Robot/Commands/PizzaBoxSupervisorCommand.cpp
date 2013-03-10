#include "PizzaBoxSupervisorCommand.h"

/*
 * Command that oversees operation of pizza box.  It responds through external commanding.
 */
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
		this->intermediateState = Idle;
	}
	else
	{
		printf("Pizza box not at top limit, moving to first loading position\n");
		pizzaBoxSubsystem->SetCurrentState(PizzaBoxSubsystem::MovingToNextLoadingPosition);
		pizzaBoxSubsystem->SetCurrentPosition(0);
		this->intermediateState = Idle;
	}	
}

void PizzaBoxSupervisorCommand::Execute() {
	this->UpdateDashboard(pizzaBoxSubsystem->GetCurrentState());
	
	switch (pizzaBoxSubsystem->GetCurrentState())
	{
		case PizzaBoxSubsystem::FiringPosition:
		case PizzaBoxSubsystem::LoadingPosition:
			// do nothing
			this->intermediateState = Idle;
			break;
		case PizzaBoxSubsystem::MovingToNextLoadingPosition:

			switch (this->intermediateState)
			{
				case Idle:
//					printf("MovingToNextLoadingPosition: Idle; starting move to next loading position\n");
					this->StartMoveToNextLoadingPosition();
					
					break;
				case MovingToLoadingSwitchOff:
//					printf("MovingToNextLoadingPosition: MovingToLoadingSwitchOff\n");
					if (!sensorSubsystem->GetPizzaLowerLimitSwitch())
					{
						this->intermediateState = MovingToLoadingSwitchOn;
					}
					this->MovePizzaBoxUp();
					
					break;
				case MovingToLoadingSwitchOn:
//					printf("MovingToNextLoadingPosition: MovingToLoadingSwitchOn");
					if (sensorSubsystem->GetPizzaLowerLimitSwitch())
					{
						this->StopPizzaBox();
						this->intermediateState = Idle;
						this->pizzaBoxSubsystem->SetCurrentState(PizzaBoxSubsystem::LoadingPosition);
						int newPosition = pizzaBoxSubsystem->GetCurrentPosition() + 1;
						this->pizzaBoxSubsystem->SetCurrentPosition(newPosition);
//						printf(": Moved into position %d\n", newPosition);
					}
					else
					{
						this->MovePizzaBoxUp();
						printf("\n");
					}
					
					break;
				case MovingToBottom:
//					printf("MovingToNextLoadingPosition: MovingToBottom\n");
					if (sensorSubsystem->GetPizzaBottomLimitSwitch())
					{
						this->StopPizzaBox();
						this->intermediateState = MovingToLoadingSwitchOn;
					}
					
					break;
				default:
//					printf("MovingToNextLoadingPosition: Error - stopping default %d\n", this->intermediateState);
					this->StopPizzaBox();
					break;
			}
			break;
		case PizzaBoxSubsystem::MovingToNextFiringPosition:
			switch (this->intermediateState)
			{
				case Idle:
//					printf("MovingToNextFiringPosition: InPosition - starting move to next fire position\n");
					this->StartMoveToNextFiringPosition();
					
					break;
				case MovingToFiringSwitchOff:
//					printf("MovingToNextFiringPosition: MovingToFiringSwitchOff\n");
					if (!sensorSubsystem->GetPizzaUpperLimitSwitch())
					{
						this->intermediateState = MovingToFiringSwitchOn;
					}
					this->MovePizzaBoxDown();
					
					break;
				case MovingToFiringSwitchOn:
//					printf("MovingToNextFiringPosition MovingToFiringSwitchOn");
					if (sensorSubsystem->GetPizzaUpperLimitSwitch())
					{
						this->StopPizzaBox();
						this->intermediateState = Idle;
						pizzaBoxSubsystem->SetCurrentState(PizzaBoxSubsystem::FiringPosition);
						int newPosition = pizzaBoxSubsystem->GetCurrentPosition() + 1;
						pizzaBoxSubsystem->SetCurrentPosition(newPosition);
//						printf(" - Stopping; new position: %d\n", newPosition);
					}
					else
					{
						this->MovePizzaBoxDown();
						printf("\n");
					}
					
					break;
				case MovingToTop:
//					printf("MovingToNextFiringPosition: MovingToTop\n");
					if (sensorSubsystem->GetPizzaTopLimitSwitch())
					{
						this->StopPizzaBox();
						this->intermediateState = MovingToFiringSwitchOn;
					}
					
					break;
				default:
//					printf("MovingToNextFiringPosition stopping on default %d\n", this->intermediateState);
					pizzaBoxSubsystem->Stop();
					break;
			}
			break;
		case PizzaBoxSubsystem::Unknown:
//			printf("Unknown state.\n");
			pizzaBoxSubsystem->SetCurrentPosition(0);
			this->StopPizzaBox();
			this->StartMoveToNextFiringPosition();
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
	default:
		message = "Unknown state";
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
//		printf("StartMoveToNextLoadingPosition: Current position 0\n");
		if (pizzaBoxSubsystem->IsAtBottomLimit()) {
//			printf("StartMoveToNextLoadingPosition: Is at bottom limit\n");
			if (pizzaBoxSubsystem->IsLoadingSwitchOn())
			{
//				printf("StartMoveToNextLoadingPosition: Loading switch on\n ");
				// We are done, don't need to load anything.
				
				pizzaBoxSubsystem->Stop();
				pizzaBoxSubsystem->SetCurrentPosition(1);
				pizzaBoxSubsystem->SetCurrentState(PizzaBoxSubsystem::LoadingPosition);
				return;
			}
			else
			{
//				printf("StartMoveToNextLoadingPosition: Loading switch off\n");
				this->intermediateState = MovingToLoadingSwitchOn;
				pizzaBoxSubsystem->MoveUp();
//				printf("StartMoveToNextLoadingPosition: At bottom, moving to first loading position\n");
			}
		}
		else
		{
			this->intermediateState = MovingToBottom;
			pizzaBoxSubsystem->MoveDown();
//			printf("StartMoveToNextLoadingPosition: Moving to bottom\n");
		}
	} 
	else
	{
//		printf("StartMoveToNextLoadingPosition:Moving to next loading position\n");
		if (pizzaBoxSubsystem->GetCurrentPosition() == MAX_FRISBEES)
		{
//			printf("StartMoveToNextLoadingPosition: Error -- pizza box is already in loading position 4\n");
			return;
		}

		if (sensorSubsystem->GetPizzaLowerLimitSwitch())
		{
//			printf("StartMoveToNextLoadingPosition: Moving to loading switch off\n");
			this->intermediateState = MovingToLoadingSwitchOff;
		}
		else
		{
			// Perhaps the box has been nudged a bit and it is below the limit switch.
			// A crappy way to recover but we'll just wait for the lower switch to come on.
			
			// Maybe we'd be better off giving up here.
			
//			printf("StartMoveToNextLoadingPosition: StartLoadIndex but lower switch is off.");
			this->intermediateState = MovingToLoadingSwitchOn;
		}
		pizzaBoxSubsystem->MoveUp();
		
		return;
	}
	
}

void PizzaBoxSupervisorCommand::StartMoveToNextFiringPosition()
{
	if (pizzaBoxSubsystem->GetCurrentPosition() == 0)
	{
//		printf("StartMoveToNextFiringPosition: current position 0\n");
		if (pizzaBoxSubsystem->IsAtTopLimit()) {
//			printf("StartMoveToNextFiringPosition: is at top limit\n");
			
			if (pizzaBoxSubsystem->IsFiringSwitchOn())
			{
//				printf("StartMoveToNextFiringPosition: firing switch on\n");
				// We are done, don't need to load anything.
				
				pizzaBoxSubsystem->Stop();
				pizzaBoxSubsystem->SetCurrentPosition(1);
				pizzaBoxSubsystem->SetCurrentState(PizzaBoxSubsystem::FiringPosition);
				
				return;
			}
			else
			{
				this->intermediateState = MovingToFiringSwitchOn;
				pizzaBoxSubsystem->MoveDown();
//				printf("StartMoveToNextFiringPosition: At top, moving to first firing position\n");
			}
		}
		else
		{
			this->intermediateState = MovingToTop;
			pizzaBoxSubsystem->MoveUp();
//			printf("StartMoveToNextFiringPosition: Moving to top\n");
		}
	} 
	else
	{
//		printf("StartMoveToNextFiringPosition: Moving to next firing position\n");
		if (pizzaBoxSubsystem->GetCurrentPosition() == MAX_FRISBEES)
		{
//			printf("StartMoveToNextFiringPosition: Error -- pizza box is already in firing position 4\n");
			return;
		}

		if (sensorSubsystem->GetPizzaUpperLimitSwitch())
		{
//			printf("StartMoveToNextFiringPosition: moving to firing siwtch off\n");
			this->intermediateState = MovingToFiringSwitchOff;
		}
		else
		{
			// Perhaps the box has been nudged a bit and it is below the limit switch.
			// A crappy way to recover but we'll just wait for the lower switch to come on.
			
			// Maybe we'd be better off giving up here, or moving back to top?
			
//			printf("StartMoveToNextFiringPosition: StartLoadIndex but lower switch is off.");
			this->intermediateState = MovingToFiringSwitchOn;
		}
		this->MovePizzaBoxDown();
		
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

void PizzaBoxSupervisorCommand::MovePizzaBoxUp() {
	if (sensorSubsystem->IsKickerStowed())
	{
		pizzaBoxSubsystem->MoveUp();
	}
	else
	{
		printf("PizzaBoxSupervisorCommand: waiting to move up\n");
	}
}

void PizzaBoxSupervisorCommand::MovePizzaBoxDown() {
	if (sensorSubsystem->IsKickerStowed())
	{
		pizzaBoxSubsystem->MoveDown();
	}
	else
	{
		printf("PizzaBoxSupervisorCommand: waiting to move down\n");
	}
}

void PizzaBoxSupervisorCommand::StopPizzaBox() {
	pizzaBoxSubsystem->Stop();
}
