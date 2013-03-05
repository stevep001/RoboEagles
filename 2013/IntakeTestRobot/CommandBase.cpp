#include "CommandBase.h"
#include "Subsystems/SensorSubsystem.h"
#include "Subsystems/FrisbeePanSubsystem.h"
#include "Subsystems/ChassisSubsystem.h"
#include "Subsystems/LcdDisplaySubsystem.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

// Initialize a single static instance of all of your subsystems to NULL
FrisbeePanSubsystem* CommandBase::frisbeePanSubsystem = NULL;
SensorSubsystem* CommandBase::sensorSubsystem = NULL;
ChassisSubsystem* CommandBase::chassisSubsystem = NULL;
LcdDisplaySubsystem* CommandBase::lcdDisplaySubsystem = NULL;
OI* CommandBase::oi = NULL;

void CommandBase::init() {
    // Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	sensorSubsystem = new SensorSubsystem();
	lcdDisplaySubsystem = new LcdDisplaySubsystem();
	frisbeePanSubsystem = new FrisbeePanSubsystem(sensorSubsystem);
	chassisSubsystem = new ChassisSubsystem();
	
	oi = new OI();
}
