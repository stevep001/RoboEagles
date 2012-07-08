#include "DriveForwardToFloorTransitionCommand.h"

/**
 * This command drives forward until there is an observed floor sensor transition, either from 
 * dark to light or light to dark
 */
DriveForwardToFloorTransitionCommand::DriveForwardToFloorTransitionCommand() {
	Requires(chassis);
}

void DriveForwardToFloorTransitionCommand::Initialize() {
	this->startingSensorState = sensorSubsystem->IsFloorDark();
	printf("DriveForwardToFloorTransitionCommand: initial state %d", this->startingSensorState);
}

void DriveForwardToFloorTransitionCommand::Execute() {
	chassis->goStraight(-0.5);
}

bool DriveForwardToFloorTransitionCommand::IsFinished() {
	return this->startingSensorState != sensorSubsystem->IsFloorDark();
}

void DriveForwardToFloorTransitionCommand::End() {
	chassis->goStraight(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveForwardToFloorTransitionCommand::Interrupted() {
	chassis->goStraight(0);
}
