#include "CameraControlCommand.h"
#include "../Subsystems/CameraControlSubsystem.h"

CameraControlCommand::CameraControlCommand() {
	Requires(cameraControlSubsystem);
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void CameraControlCommand::Initialize() {
	printf("CameraControlCommand initialized\n");
}

// Called repeatedly when this Command is scheduled to run
void CameraControlCommand::Execute() {
	float position = oi->GetJoystick()->GetY();
	if (position < 0) {
		position = 0;
	}
	
	cameraControlSubsystem->Move(position);
}

// Make this return true when this Command no longer needs to run execute()
bool CameraControlCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CameraControlCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CameraControlCommand::Interrupted() {
}
