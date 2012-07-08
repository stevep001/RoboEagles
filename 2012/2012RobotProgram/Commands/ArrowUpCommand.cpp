#include "ArrowUpCommand.h"

/**
 * Controls the up arrow on the Traffic Cop
 */
ArrowUpCommand::ArrowUpCommand() : CommandBase("ArrowUpCommand") {
	Requires(trafficCopSubsystem);
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void ArrowUpCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void ArrowUpCommand::Execute() {
	trafficCopSubsystem->ArrowUp();
}

// Make this return true when this Command no longer needs to run execute()
bool ArrowUpCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ArrowUpCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArrowUpCommand::Interrupted() {
}
