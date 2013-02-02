#include "MovePBBottomCommand.h"

MovePBBottomCommand::MovePBBottomCommand() {
	// Use Requires() here to declare subsystem dependencies
	Requires(pizzaBoxSubsystem);
}

// Called just before this Command runs the first time
void MovePBBottomCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void MovePBBottomCommand::Execute() {
	pizzaBoxSubsystem->MoveBottom();
}

// Make this return true when this Command no longer needs to run execute()
bool MovePBBottomCommand::IsFinished() {
	return pizzaBoxSubsystem->IsAtBottom();
}

// Called once after isFinished returns true
void MovePBBottomCommand::End() {
	pizzaBoxSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MovePBBottomCommand::Interrupted() {
	pizzaBoxSubsystem->Stop();
}
