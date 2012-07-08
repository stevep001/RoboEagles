#include "ArrowDownCommand.h"

/**
 * Controls the down arrow on the Traffic Cop
 */
ArrowDownCommand::ArrowDownCommand() : CommandBase("ArrowDownCommand") {
	Requires(trafficCopSubsystem);
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void ArrowDownCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void ArrowDownCommand::Execute() {
	trafficCopSubsystem->ArrowDown();
}

// Make this return true when this Command no longer needs to run execute()
bool ArrowDownCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ArrowDownCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArrowDownCommand::Interrupted() {
}
