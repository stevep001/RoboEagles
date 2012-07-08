#include "BeltCommand.h"


BeltCommand::BeltCommand(bool on) :CommandBase("BeltCommand") {
	Requires(ballLoaderSubsystem);
	printf("Initalizing BeltCommand: commanded state: %d\n", on);
	this->on = on;
	this->finished = false;
}

// Called just before this Command runs the first time
void BeltCommand::Initialize() {
	this->finished = false;
}

// Called repeatedly when this Command is scheduled to run
void BeltCommand::Execute() {
	if (this->on)
	{
		ballLoaderSubsystem->BeltUp();
		printf("BeltCommand Up\n");
	} else {
		ballLoaderSubsystem->BeltOff();
		printf("BeltCommand off\n");
	}	
	this->finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool BeltCommand::IsFinished() {
	return finished;
}

// Called once after isFinished returns true
void BeltCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BeltCommand::Interrupted() {
}
