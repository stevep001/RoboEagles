#include "ShooterSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/ShooterSupervisorCommand.h"

ShooterSubsystem::ShooterSubsystem() : Subsystem("ShooterSubsystem") {
	printf("ShooterSubsystem: constructor starting\n");
	this->shooterMotor = new Jaguar(PWM_SLOT, SHOOTER_MOTOR);
	this->shootingPower = Normal;
	printf("ShooterSubsystem: constructor completed.\n");
}
    
void ShooterSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new ShooterSupervisorCommand());
}

void ShooterSubsystem::SetShootingPower(ShooterPower desiredPower) {
	this->shootingPower = desiredPower;
}

ShooterSubsystem::ShooterPower ShooterSubsystem::GetShootingPower()
{
	return this->shootingPower;
}

SpeedController* ShooterSubsystem::GetMotor()
{
	return this->shooterMotor;
}
