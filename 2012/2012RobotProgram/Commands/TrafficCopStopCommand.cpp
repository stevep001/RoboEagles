#include "TrafficCopStopCommand.h"

TrafficCopStopCommand::TrafficCopStopCommand() : CommandBase("TrafficCopStopCommand") {
	Requires(trafficCopSubsystem);
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void TrafficCopStopCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void TrafficCopStopCommand::Execute() {
	trafficCopSubsystem->Stop();
}

// Make this return true when this Command no longer needs to run execute()
bool TrafficCopStopCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void TrafficCopStopCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TrafficCopStopCommand::Interrupted() {
}
