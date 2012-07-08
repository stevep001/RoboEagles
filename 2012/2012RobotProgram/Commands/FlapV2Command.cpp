#include "FlapV2Command.h"

FlapV2Command::FlapV2Command(bool moveDown): CommandBase("FlapV2Command") {
	Requires(ballLoaderSubsystem);
	this->moveDown = moveDown;
	this->toggle = false;
}

FlapV2Command::FlapV2Command() : CommandBase("FlapV2Command") {
	Requires(ballLoaderSubsystem);
	this->toggle = true;
}

// Called just before this Command runs the first time
void FlapV2Command::Initialize() {
	if (toggle)
	{
		flapDown = !flapDown;
	}
	else
	{
		flapDown = moveDown;
	}
	
	if (flapDown){
		printf("FlapV2Command down\n");
		ballLoaderSubsystem->FlapDown();	
	}
	else {
		printf("FlapV2Command up\n");
		ballLoaderSubsystem->FlapUp();
	}	
}

// Called repeatedly when this Command is scheduled to run
void FlapV2Command::Execute() {
	
}



// Make this return true when this Command no longer needs to run execute()
bool FlapV2Command::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void FlapV2Command::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FlapV2Command::Interrupted() {
}
