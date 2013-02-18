#include "OnFrisbeeArrivalCommand.h"

OnFrisbeeArrivalCommand::OnFrisbeeArrivalCommand() {
	Requires(pizzaBoxSubsystem);
	prepareForFiring = false;
}

// Called just before this Command runs the first time
void OnFrisbeeArrivalCommand::Initialize() {
//	if(pizzaBoxSubsystem->IsBoxFull()) {
//		prepareForFiring = true;
//		pizzaBoxSubsystem->StartMoveFirstFiringPosition();
//	} else {
//		pizzaBoxSubsystem->StartMoveNextLoadingPosition();
//	}
}

// Called repeatedly when this Command is scheduled to run
void OnFrisbeeArrivalCommand::Execute() {
//	if(prepareForFiring){
//		pizzaBoxSubsystem->MoveFirstFiringPosition();
//	}else{
//		pizzaBoxSubsystem->MoveToNextLoadingPosition();
//	}
}

// Make this return true when this Command no longer needs to run execute()
bool OnFrisbeeArrivalCommand::IsFinished() {
//	if(prepareForFiring){
//		return pizzaBoxSubsystem->IsInFiringPosition(); 
//	}else {	
//		return pizzaBoxSubsystem->IsInLoadingPosition();
//	}
	return true; // temp
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
