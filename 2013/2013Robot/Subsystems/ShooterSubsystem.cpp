#include "ShooterSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/ShooterSupervisorCommand.h"

#define MAX_SHOOTING_POWER	80
#define	MIN_SHOOTING_POWER	30

ShooterSubsystem::ShooterSubsystem() : Subsystem("ShooterSubsystem") {
	printf("ShooterSubsystem: constructor starting\n");
	this->shooterMotor = new Jaguar(PWM_SLOT, SHOOTER_MOTOR);
	this->shootingPower = MIN_SHOOTING_POWER;
	printf("ShooterSubsystem: constructor completed.\n");
}
    
void ShooterSubsystem::InitDefaultCommand() {
	//SetDefaultCommand(new ShooterSupervisorCommand());
}

void ShooterSubsystem::SetShootingPower(float power) {
	this->shooterMotor->Set(-power);
}

SpeedController* ShooterSubsystem::GetMotor()
{
	return this->shooterMotor;
}
