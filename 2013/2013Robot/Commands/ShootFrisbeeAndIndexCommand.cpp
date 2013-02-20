#include "ShootFrisbeeAndIndexCommand.h"

ShootFrisbeeAndIndexCommand::ShootFrisbeeAndIndexCommand() {

}

// Called just before this Command runs the first time
void ShootFrisbeeAndIndexCommand::Initialize() {
	this->state = Starting;
}

// Called repeatedly when this Command is scheduled to run
void ShootFrisbeeAndIndexCommand::Execute() {
	switch (this->state)
	{
	case Starting:
		printf("Starting\n");
		if (pizzaBoxSubsystem->IsInFiringPosition())
		{
			this->state = StartFiring;
		}
		else
		{
			pizzaBoxSubsystem->MoveFirstFiringPosition();
			this->state = MovingToNextFiringPosition;
		}
		break;
		
	case StartFiring:
		printf("StartFiring\n");
		kickerSubsystem->Kick();
		this->state = WaitingForKickerToComplete;
		break;
		
	case WaitingForKickerToComplete:
		printf("Waiting for kick to complete\n");
		if (kickerSubsystem->IsStowed())
		{
			if (pizzaBoxSubsystem->CanMoveNextFiringPosition())
			{
				pizzaBoxSubsystem->MoveNextFiringPosition();
				this->state = MovingToNextFiringPosition;
			}
			else
			{
				pizzaBoxSubsystem->MoveFirstLoadingPosition();
				this->state = Done;
			}
		}
		break;
		
	case MovingToNextFiringPosition:
		printf("Moving to next firing position\n");
		if (pizzaBoxSubsystem->IsInFiringPosition()) {
			this->state = StartFiring;
		}
		break;
		
	default:
		printf("ShootFrisbeeAndIndexCommand: unknown stated %d\n", this->state);
		break;
	}
	
}

// Make this return true when this Command no longer needs to run execute()
bool ShootFrisbeeAndIndexCommand::IsFinished() {
	return this->state == Done;
}

// Called once after isFinished returns true
void ShootFrisbeeAndIndexCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootFrisbeeAndIndexCommand::Interrupted() {
}

