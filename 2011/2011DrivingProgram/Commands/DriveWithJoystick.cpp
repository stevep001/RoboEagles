#include "DriveWithJoystick.h"

DriveWithJoystick::DriveWithJoystick() {
	Requires(chassis);
}

// Called just before this Command runs the first time
void DriveWithJoystick::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {
	//chassis->driveWithJoystick(oi->getJoystick());
	
	// get y value from joystick
	//double leftY = oi->getLeftJoystick()->GetY();
	//double rightY = oi->getRightJoystick()->GetY();
	
	double leftY = oi->getLeftKinectStick()->GetY();
	double rightY = oi->getRightKinectStick()->GetY();
	chassis->tankDrive(leftY / 1.5, rightY / 1.5);

	//chassis->driveWithKinectStick(oi->getKinectStick());
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoystick::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveWithJoystick::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithJoystick::Interrupted() {
}
