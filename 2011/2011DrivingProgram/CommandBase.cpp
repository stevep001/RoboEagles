#include "CommandBase.h"
#include "Commands/Scheduler.h"

// This is the base class of all of the commands you are implementing.

// Below you'll set up pointers to shared instances of all of your subsystems.

CommandBase::CommandBase(const char *name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

// Initialize a single static instance of all of your subsystems to NULL
Chassis *CommandBase::chassis = NULL;
OI* CommandBase::oi = NULL;

void CommandBase::init() {
	// Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	chassis = new Chassis();
	
	oi = new OI();
}
