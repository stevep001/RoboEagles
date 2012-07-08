#include "CannonAimSubsystem.h"
#include "../Robotmap.h"

CannonAimSubsystem::CannonAimSubsystem() : Subsystem("CannonFireSubsystem") {
downSolenoid = new Solenoid (UP_SOLENOID);
upSolenoid = new Solenoid (DOWN_SOLENOID);
printf("CannonAimSubsystem initialized\n");

}
    
void CannonAimSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void CannonAimSubsystem::Down(){
	printf("Aim down\n");
	upSolenoid->Set(false);
	downSolenoid->Set(true);		
}

void CannonAimSubsystem::Up(){
	printf("Aim up\n");
	downSolenoid->Set(false);
	upSolenoid->Set(true);
}

void CannonAimSubsystem::Stop(){
	printf("Aim stop\n");

	upSolenoid->Set(false);
	downSolenoid->Set(false);
}
