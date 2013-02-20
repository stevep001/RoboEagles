#include "PanLiftSubsystem.h"
#include "../Robotmap.h"

PanLiftSubsystem::PanLiftSubsystem() : Subsystem("PanLiftSubsystem") {
	this->panLiftMotor = new Jaguar(PWM_SLOT, PAN_LIFT_MOTOR);
}
    
void PanLiftSubsystem::InitDefaultCommand() {

}

void PanLiftSubsystem::SetSpeed(float speed)
{
	this->panLiftMotor->Set(speed);
}
