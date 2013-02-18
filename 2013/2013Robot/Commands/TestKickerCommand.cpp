#include "TestKickerCommand.h"

TestKickerCommand::TestKickerCommand() {

}

// Called just before this Command runs the first time
void TestKickerCommand::Initialize() {
	kickerSubsystem->Kick();
}

// Called repeatedly when this Command is scheduled to run
void TestKickerCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool TestKickerCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void TestKickerCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestKickerCommand::Interrupted() {
}
