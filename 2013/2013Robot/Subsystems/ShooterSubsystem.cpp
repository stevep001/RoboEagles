#include "ShooterSubsystem.h"
#include "../Robotmap.h"

ShooterSubsystem::ShooterSubsystem() : Subsystem("ShooterSubsystem") {
	printf("ShooterSubsystem: constructor starting\n");
	this->shooterJaguar = new Jaguar(PWM_SLOT, SHOOTER_MOTOR);
	printf("ShooterSubsystem: constructor completed.\n");
}
    
void ShooterSubsystem::InitDefaultCommand() {

}

void ShooterSubsystem::SetShootingPower(float power) {
	this->shooterJaguar->Set(power);
}
