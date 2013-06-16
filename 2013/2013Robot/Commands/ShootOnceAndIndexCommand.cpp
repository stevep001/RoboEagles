#include "ShootOnceAndIndexCommand.h"

ShootOnceAndIndexCommand::ShootOnceAndIndexCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void ShootOnceAndIndexCommand::Initialize() {
	printf("ShootOnceAndIndexCommand: Starting\n");
	this->state = Starting; // Sets the command state to Starting
	
}

// Called repeatedly when this Command is scheduled to run
void ShootOnceAndIndexCommand::Execute() {
	switch (this->state) {
	case Starting:
		if (pizzaBoxSubsystem->IsInFiringPosition()) {		//Checks to see if the pizza box is in it's firing position
			this->state = StartFiring; 						// Sets the state to StartFiring
		} else { 											// If the pizza box is not in its firing position it will move it so it is
			pizzaBoxSubsystem->MoveFirstFiringPosition();	// Tells the pizza box to move to it's next firing position
			this->state = MovingToNextFiringPosition; 		// Sets the state to MoveToNextFiringPosition
		}
		break;
		
	case StartFiring:	// This case will kick to frisbee in to the shooter
		printf("Starting to fire\n");
		kickerSubsystem->Kick();	// Tells the kicker to move or "Kick" the frisbee in to shooter
		
		this->state = WaitingForKickerToFinish;	// sets the sate to WaitingForKickerToFinish
		break;
		
	case WaitingForKickerToFinish: 
		printf("Waiting for the kicker to finish\n");
		if (kickerSubsystem->IsStowed()) { 							// This checks if the kicker is in it stowed position
			this->state = PostFiring;
		}
		
		break;
		
		
	case MovingToNextFiringPosition: 
		printf("Moving to next firing position\n");
		if (pizzaBoxSubsystem->IsInFiringPosition()) {
			this->state = StartFiring; // Sets the state to StartFiring
		}
		break;
	
	case PostFiring:
		if (pizzaBoxSubsystem->CanMoveNextFiringPosition()) {
			pizzaBoxSubsystem->MoveNextFiringPosition(); 
			this->state = PostFireMovingToNextFiringPosition; 			
		} else {
			pizzaBoxSubsystem->MoveFirstLoadingPosition(); 	
			this->state = PostFireMovingToFirstLoadingPosition; 		
		}
		break;
			
	case PostFireMovingToNextFiringPosition:
		printf("Waiting for PB to move to Firing Position\n");
		if (pizzaBoxSubsystem->IsInFiringPosition()) {
			this->state = Done;
		}
		break;
		
	case PostFireMovingToFirstLoadingPosition:
		printf("PB is moving to first loading position\n");
		//shooterTiltSubsystem->SetAngle(0);
		
		if (pizzaBoxSubsystem->IsInLoadingPosition()) {
			this->state = Done;
		}
		break;
		
	default:
		printf("ShootOnceAndIndex: Unknown state %d\n", this->state);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ShootOnceAndIndexCommand::IsFinished() {
	return this->state == Done;
}

// Called once after isFinished returns true
void ShootOnceAndIndexCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootOnceAndIndexCommand::Interrupted() {
}
