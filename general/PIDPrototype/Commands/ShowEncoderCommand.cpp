#include "ShowEncoderCommand.h"

ShowEncoderCommand::ShowEncoderCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void ShowEncoderCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void ShowEncoderCommand::Execute() {
	oi->DisplayEncoder(prototypingsubsystem->GetMotorEncoder());
}

// Make this return true when this Command no longer needs to run execute()
bool ShowEncoderCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ShowEncoderCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShowEncoderCommand::Interrupted() {
}
