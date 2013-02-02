#include "ThrowerSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/HorizontalAimCommand.h"

/**
 * Manages the throwing of the robot.
 */

ThrowerSubsystem::ThrowerSubsystem() : Subsystem("ThrowerSubsystem") {
	throwSolenoidOut = new Solenoid(THROW_SOLENOID_OUT);
	throwSolenoidIn = new Solenoid(THROW_SOLENOID_IN);
	aimMotor = new Jaguar(AIM_MOTOR_PWM);
	this->Retract();
}
    
void ThrowerSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new HorizontalAimCommand());
}

void ThrowerSubsystem::StartThrow() {
	throwSolenoidIn->Set(false);
	throwSolenoidOut->Set(true);
}

void ThrowerSubsystem::StopThrow() {
	throwSolenoidOut->Set(false);
} 

void ThrowerSubsystem::Retract() {
	throwSolenoidOut->Set(false);
	throwSolenoidIn->Set(true);
}

void ThrowerSubsystem::Move(double movement) {
	aimMotor->Set(movement);
}
