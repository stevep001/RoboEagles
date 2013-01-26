#include "CommandBase.h"
#include "Subsystems/PrototypingSubsystem.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

// Initialize a single static instance of all of your subsystems to NULL
PrototypingSubsystem* CommandBase::prototypingsubsystem = NULL;
OI* CommandBase::oi = NULL;

void CommandBase::init() {
    // Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	prototypingsubsystem = new PrototypingSubsystem();
	oi = new OI();
}
