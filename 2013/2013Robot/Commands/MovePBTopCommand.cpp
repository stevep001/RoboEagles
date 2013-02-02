#include "MovePBTopCommand.h"

MovePBTopCommand::MovePBTopCommand() {
	// Use Requires() here to declare subsystem dependencies
	Requires(pizzaBoxSubsystem);
}

// Called just before this Command runs the first time
void MovePBTopCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void MovePBTopCommand::Execute() {
	pizzaBoxSubsystem->MoveTop();
}

// Make this return true when this Command no longer needs to run execute()
bool MovePBTopCommand::IsFinished() {
	return pizzaBoxSubsystem->IsAtTop();
}

// Called once after isFinished returns true
void MovePBTopCommand::End() {
	pizzaBoxSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MovePBTopCommand::Interrupted() {
	pizzaBoxSubsystem->Stop();	
}
