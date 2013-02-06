#include "DriveWithJoystick.h"

DriveWithJoystick::DriveWithJoystick() : CommandBase("DriveWithJoystick"){
	Requires(chassis);
}

void DriveWithJoystick::Initialize() {
	chassis->disableBrakeMode();
	chassis->stop();
}

void DriveWithJoystick::Execute() {
	float y = oi->getRightJoystick()->GetY();
	float x = oi->getRightJoystick()->GetX();
	
	SmartDashboard::PutNumber("Forward power", y);
	SmartDashboard::PutNumber("Left X", x);
	
	
	// oi->getSmartDashboard()->PutDouble("Forward power", y);
	// oi->getSmartDashboard()->PutDouble("Left X", x);
	chassis->driveWithJoystick(oi->getRightJoystick());
	
	//chassis->tankDrive(leftY, rightY);
	
	//chassis->driveWithKinectStick(oi->getKinectStick());
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveWithJoystick::End() {
	chassis->stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithJoystick::Interrupted() {
	chassis->stop();
}
