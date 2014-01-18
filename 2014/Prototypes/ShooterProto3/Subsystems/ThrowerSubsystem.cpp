#include "ThrowerSubsystem.h"
#include "../Robotmap.h"

ThrowerSubsystem::ThrowerSubsystem() : Subsystem("ThrowerSubsystem") {
	this->throwerSolenoid = new DoubleSolenoid(FORWARD_SOLENOID, BACKWARD_SOLENOID);
	this->secThrowerSolenoid = new DoubleSolenoid(FORWARD_SOLENOID_2, BACKWARD_SOLENOID_2);
}
    
void ThrowerSubsystem::InitDefaultCommand() {
}

void ThrowerSubsystem::Open() {
	this->throwerSolenoid->Set(DoubleSolenoid::kForward);
	this->secThrowerSolenoid->Set(DoubleSolenoid::kForward);
}

void ThrowerSubsystem::Close() {
	this->throwerSolenoid->Set(DoubleSolenoid::kReverse);
	this->secThrowerSolenoid->Set(DoubleSolenoid::kReverse);
}

void ThrowerSubsystem::Stop() {
	this->throwerSolenoid->Set(DoubleSolenoid::kOff);
	this->secThrowerSolenoid->Set(DoubleSolenoid::kOff);
}
