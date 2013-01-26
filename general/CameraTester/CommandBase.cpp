#include "CommandBase.h"
#include "Subsystems/CameraControlSubsystem.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

// Initialize a single static instance of all of your subsystems to NULL
CameraControlSubsystem* CommandBase::cameraControlSubsystem = NULL;
OI* CommandBase::oi = NULL;

void CommandBase::init() {
    // Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	cameraControlSubsystem = new CameraControlSubsystem();
	oi = new OI();
}
