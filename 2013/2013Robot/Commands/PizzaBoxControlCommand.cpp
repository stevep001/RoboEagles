#include "PizzaBoxControlCommand.h"

PizzaBoxControlCommand::PizzaBoxControlCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void PizzaBoxControlCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void PizzaBoxControlCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool PizzaBoxControlCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void PizzaBoxControlCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PizzaBoxControlCommand::Interrupted() {
}
