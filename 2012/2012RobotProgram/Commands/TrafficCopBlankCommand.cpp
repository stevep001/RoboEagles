#include "TrafficCopBlankCommand.h"

TrafficCopBlankCommand::TrafficCopBlankCommand() : CommandBase("TrafficCopBlankCommand") {
	Requires(trafficCopSubsystem);
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void TrafficCopBlankCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void TrafficCopBlankCommand::Execute() {
	trafficCopSubsystem->Blank();
}

// Make this return true when this Command no longer needs to run execute()
bool TrafficCopBlankCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void TrafficCopBlankCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TrafficCopBlankCommand::Interrupted() {
}
