#include "CommandBase.h"
#include "Subsystems/Chassis.h"
#include "Commands/Scheduler.h"
#include "Subsystems/CompressorSubsystem.h"
#include "Subsystems/ThrowerSubsystem.h"
#include "Subsystems/BallLoaderSubsystem.h"
#include "Subsystems/LifterSubsystem.h"
#include "Subsystems/SensorSubsystem.h"
#include "Subsystems/TrafficCopSubsystem.h"
#include "Subsystems/LCDSubsystem.h"

CommandBase::CommandBase(const char *name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}
OI *CommandBase::oi = NULL;

// Initialize a single static instance of all of your subsystems to NULL
BallLoaderSubsystem *CommandBase::ballLoaderSubsystem = NULL;
Chassis *CommandBase::chassis = NULL;
CompressorSubsystem *CommandBase::compressorSubsystem = NULL;
LifterSubsystem *CommandBase::lifterSubsystem = NULL;
SensorSubsystem *CommandBase::sensorSubsystem = NULL;
ThrowerSubsystem *CommandBase::throwerSubsystem = NULL;
TrafficCopSubsystem *CommandBase::trafficCopSubsystem = NULL;
LCDSubsystem *CommandBase::lcdSubsystem = NULL;
CameraControlSubsystem *CommandBase::cameraControlSubsystem = NULL;

int CommandBase::throwerPower = MAX_THROWING_POWER;
bool CommandBase::flapDown = true;
int CommandBase::autonomousProgram = MIN_AUTONOMOUS_MODE;

void CommandBase::init() {
	ballLoaderSubsystem = new BallLoaderSubsystem();
	chassis = new Chassis();
	compressorSubsystem = new CompressorSubsystem();
	lifterSubsystem = new LifterSubsystem();
	sensorSubsystem = new SensorSubsystem();
	throwerSubsystem = new ThrowerSubsystem();
	trafficCopSubsystem = new TrafficCopSubsystem();
	cameraControlSubsystem = new CameraControlSubsystem();
	
	lcdSubsystem = new LCDSubsystem();
	lcdSubsystem->UpdateAutonomousProgram(CommandBase::autonomousProgram);
	lcdSubsystem->UpdateThrowingPower(CommandBase::throwerPower);
	
	// This needs to occur after all subsystems are present
	oi = new OI();
}
