#include "LifterSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/LifterManualCommand.h"

/**
 * Controls the lifter on the front of the robot.
 */
LifterSubsystem::LifterSubsystem() : Subsystem("LifterSubsystem") {
	lifterSolenoidDown = new Solenoid(LIFTER_SOLENOID_DOWN);
	lifterSolenoidUp = new Solenoid(LIFTER_SOLENOID_UP);
	lifterSolenoidUp->Set(true);
}
    
void LifterSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new LifterManualCommand());
}

void LifterSubsystem::LiftUp() {
	lifterSolenoidDown->Set(false);
	lifterSolenoidUp->Set(true);
}

void LifterSubsystem::LiftDown() {
	lifterSolenoidUp->Set(false);
	lifterSolenoidDown->Set(true);
}

void LifterSubsystem::LiftStop() {
	lifterSolenoidUp->Set(false);
	lifterSolenoidDown->Set(false);
}

