#include "TestTiltCommand.h"

TestTiltCommand::TestTiltCommand(float power) {
	Requires(shooterTiltSubsystem);
	this->power = power;
}

// Called just before this Command runs the first time
void TestTiltCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void TestTiltCommand::Execute() {
	printf("TestTiltCommand: power set to %f\n", power);
	shooterTiltSubsystem->GetMotor()->Set(power);
}

// Make this return true when this Command no longer needs to run execute()
bool TestTiltCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TestTiltCommand::End() {
	shooterTiltSubsystem->GetMotor()->Set(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestTiltCommand::Interrupted() {
	shooterTiltSubsystem->GetMotor()->Set(0);
}
