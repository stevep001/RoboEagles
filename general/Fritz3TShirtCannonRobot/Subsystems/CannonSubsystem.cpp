#include "CannonSubsystem.h"
#include "../Robotmap.h"

CannonSubsystem::CannonSubsystem() : Subsystem("CannonSubsystem") {
	fillSolenoid = new Solenoid(FILL_SOLENOID);
	fireSolenoid = new Solenoid(FIRE_SOLENOID);
	Stop();
	printf("CannonSubsystem initialized\n");
}
    
void CannonSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void CannonSubsystem::Fill() {
	printf("Filling\n");
	fillSolenoid->Set(true);
	fireSolenoid->Set(false);
}

void CannonSubsystem::Fire() {
	printf("Firing\n");
	fillSolenoid->Set(false);
	fireSolenoid->Set(true);
}

void CannonSubsystem::Stop() {
	fillSolenoid->Set(false);
	fireSolenoid->Set(false);
}
