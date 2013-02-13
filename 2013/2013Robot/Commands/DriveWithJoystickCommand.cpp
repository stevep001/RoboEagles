#include "DriveWithJoystickCommand.h"
#include "..\Subsystems\Chassis.h"

DriveWithJoystickCommand::DriveWithJoystickCommand() {
	Requires(chassis);
}

// Called just before this Command runs the first time
void DriveWithJoystickCommand::Initialize() {
	chassis->Stop();
}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystickCommand::Execute() {
	chassis->Drive(oi->GetDriverJoystick());
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoystickCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveWithJoystickCommand::End() {
	chassis->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithJoystickCommand::Interrupted() {
	chassis->Stop();
}
