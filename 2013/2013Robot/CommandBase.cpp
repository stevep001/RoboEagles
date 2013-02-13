#include "CommandBase.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

// Initialize a single static instance of all of your subsystems to NULL
PizzaBoxSubsystem* CommandBase::pizzaBoxSubsystem = NULL;
SensorSubsystem* CommandBase::sensorSubsystem = NULL;
ShooterTiltSubsystem* CommandBase::shooterTiltSubsystem = NULL;
Chassis *CommandBase::chassis = NULL;
OI* CommandBase::oi = NULL;

void CommandBase::init() {
    // Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	pizzaBoxSubsystem = new PizzaBoxSubsystem();
	sensorSubsystem = new SensorSubsystem();
	chassis = new Chassis();
	shooterTiltSubsystem = new ShooterTiltSubsystem();
	
	oi = new OI();
}
