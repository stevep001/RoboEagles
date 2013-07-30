#include "ProcessVisionCommand.h"

ProcessVisionCommand::ProcessVisionCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	printf("[ProcessVisionCommand] Constructing\n");
	Requires(visionSubsystemV2);
	printf("[ProcessVisionCommand] Constructed\n");
}

// Called just before this Command runs the first time
void ProcessVisionCommand::Initialize() {
	timer = new Timer();
	
	distance = -1.0;
	azimuth = -1.0;
	
	visionSubsystemV2->ProcessCameraImage();
	timer->Reset();
	timer->Start();
}

// Called repeatedly when this Command is scheduled to run
void ProcessVisionCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool ProcessVisionCommand::IsFinished() {
	return visionSubsystemV2->IsImageProcessed();
}

// Called once after isFinished returns true
void ProcessVisionCommand::End() {
	timer->Stop();
	printf("[ProcessVisionCommand] It took %f seconds to process\n",timer->Get());
	if (visionSubsystemV2->IsHighTargetVisable() || visionSubsystemV2->IsMiddleTargetVisable() || visionSubsystemV2->IsSecondMiddleTargetVisable()) {
		targetsVisable = true;
	} else {
		targetsVisable = false;
	}
	
	if(visionSubsystemV2->IsHighTargetVisable()) {
		distance = visionSubsystemV2->GetHighTargetDistance();
		azimuth = visionSubsystemV2->GetHighTargetAzimuth();
		shooterTiltAngle = computeTiltAngle(distance);
	} else if(visionSubsystemV2->IsMiddleTargetVisable()) {
		distance = visionSubsystemV2->GetMiddleTargetDistance();
		azimuth = visionSubsystemV2->GetMiddleTargetAzimuth();
		shooterTiltAngle = computeTiltAngle(distance);
	} else if(visionSubsystemV2->IsSecondMiddleTargetVisable()){
		distance = visionSubsystemV2->GetSecondMiddleTargetDistance();
		azimuth = visionSubsystemV2->GetSecondMiddleTargetAzimuth();
		shooterTiltAngle = computeTiltAngle(distance);
	} 
	printf("[ProcessVisionCommand] Ending\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ProcessVisionCommand::Interrupted() {
	printf("[ProcessVisionCommand] Interrupted\n");
}

float ProcessVisionCommand::GetDistance() {
	return distance;
}

float ProcessVisionCommand::GetAzimuth() {
	return azimuth;
}

float ProcessVisionCommand::computeTiltAngle(float distance){
	float tiltAngle;
	if ((distance <= TILT_ANGLE_22) && (distance >= TILT_ANGLE_24)) {
		tiltAngle = 22;
	} else if ((distance <= TILT_ANGLE_24) && (distance >= TILT_ANGLE_26)) {
		tiltAngle = 24;
	} else if ((distance <= TILT_ANGLE_26) && (distance >= TILT_ANGLE_28)) {
		tiltAngle = 26;
	} else if ((distance <= TILT_ANGLE_28) && (distance >= TILT_ANGLE_30)) {
		tiltAngle = 28;
	} else if ((distance <= TILT_ANGLE_30) && (distance >= TILT_ANGLE_32)) {
		tiltAngle = 30;
	} else if ((distance <= TILT_ANGLE_32) && (distance >= TILT_ANGLE_34)) {
		tiltAngle = 32;
	} else if ((distance <= TILT_ANGLE_34) && (distance >= TILT_ANGLE_36)) {
		tiltAngle = 34;
	} else if ((distance <= TILT_ANGLE_36) && (distance >= TILT_ANGLE_38)) {
		tiltAngle = 36;
	} else if ((distance <= TILT_ANGLE_38) && (distance >= TILT_ANGLE_40)) {
		tiltAngle = 38;
	} else {
		tiltAngle = -1;
	}
	return tiltAngle;
}

bool ProcessVisionCommand::AreTargetsVisable() {
	return targetsVisable;
}

float ProcessVisionCommand::GetTiltAngle() {
	return shooterTiltAngle;
}
