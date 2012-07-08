#include "StopLoadingCommand.h"

/*
 * This command stops the automated loading process
 */
StopLoadingCommand::StopLoadingCommand() {
	Requires(ballLoaderSubsystem);
	Requires(cameraControlSubsystem);
}

void StopLoadingCommand::Initialize() {
	ballLoaderSubsystem->BeltOff();
	printf("Camera to basket\n");
	cameraControlSubsystem->Move(.5);
}

void StopLoadingCommand::Execute() {
	
}


bool StopLoadingCommand::IsFinished() {
	return false;
}


void StopLoadingCommand::End() {
	
}

void StopLoadingCommand::Interrupted() {
}
