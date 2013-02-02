#include "OnFrisbeeArrivalCommand.h"

OnFrisbeeArrivalCommand::OnFrisbeeArrivalCommand() {
	Requires(pizzaBoxSubsystem);
	prepareForFiring = false;
}

// Called just before this Command runs the first time
void OnFrisbeeArrivalCommand::Initialize() {
	if(pizzaBoxSubsystem->IsBoxFull()){ // TODO finish the logic for telling when the box is full
		prepareForFiring = true;
		pizzaBoxSubsystem->StartMoveFiring();
	} else {
		pizzaBoxSubsystem->StartLoadIndex();
	}
}

// Called repeatedly when this Command is scheduled to run
void OnFrisbeeArrivalCommand::Execute() {
	if(prepareForFiring){
		pizzaBoxSubsystem->MoveFiringPosition();
	}else{
		pizzaBoxSubsystem->LoadIndex();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool OnFrisbeeArrivalCommand::IsFinished() {
	if(prepareForFiring){
		return pizzaBoxSubsystem->IsInFiringPosition(); 
	}else {	
		return pizzaBoxSubsystem->IsInLoadingPosition();
	}
}

// Called once after isFinished returns true
void OnFrisbeeArrivalCommand::End() {
	pizzaBoxSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OnFrisbeeArrivalCommand::Interrupted() {
	pizzaBoxSubsystem->Stop();
}
