#include "CommandBase.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/CannonAimSubsystem.h"
#include "Subsystems/CannonSubsystem.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

// Initialize a single static instance of all of your subsystems to NULL
	OI* CommandBase::oi = NULL;
	Chassis *CommandBase::chassis = NULL;
	CannonAimSubsystem *CommandBase::cannonAimSubsystem = NULL;
	CannonSubsystem *CommandBase::cannonSubsystem = NULL;

	

void CommandBase::init() {
    // Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	chassis = new Chassis();
	cannonAimSubsystem = new CannonAimSubsystem();
	cannonSubsystem = new CannonSubsystem();
	oi = new OI();
}
