#include "BallLoaderAutomatedCommand.h"

/**
 * This implements automation for control of the ball loading process.
 */
BallLoaderAutomatedCommand::BallLoaderAutomatedCommand() {
	Requires(ballLoaderSubsystem);
	Requires(cameraControlSubsystem);
}

void BallLoaderAutomatedCommand::Initialize() {
	printf("Initializing BallLoaderAutomatedCommand\n");
	ballLoaderSubsystem->FlapUp();
	ballLoaderSubsystem->BeltUp();
	printf("Camera to sweeper\n");
	cameraControlSubsystem->Move(0);
	this->lastBallState = false;
	printf("BallLoaderAutomatedCommand initialized\n");
}

void BallLoaderAutomatedCommand::Execute() {
	// Flap control
	
	//printf("arm %d sensor 3 %d\n", sensorSubsystem->IsArmDown(), sensorSubsystem->IsBallPresentSensor3());
	
	if (sensorSubsystem->IsArmDown()) {
		if (sensorSubsystem->IsBallPresentSensor3())
		{
			ballLoaderSubsystem->FlapUp();
		}
		else
		{
			ballLoaderSubsystem->FlapDown();
		}
	}
	else
	{
		ballLoaderSubsystem->FlapUp();
	}

	ballLoaderSubsystem->BeltUp();
}

bool BallLoaderAutomatedCommand::IsFinished() {
	return false;
}

void BallLoaderAutomatedCommand::End() {
	
}

void BallLoaderAutomatedCommand::Interrupted() {
	ballLoaderSubsystem->FlapUp();
	ballLoaderSubsystem->BeltOff();
}
