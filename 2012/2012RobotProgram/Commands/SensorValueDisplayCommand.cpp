#include "SensorValueDisplayCommand.h"



/*
 * This command runs in the SensorSubsystem, and is responsible for displaying
 * raw sensor values on the smart dashboard.
 */
SensorValueDisplayCommand::SensorValueDisplayCommand() {
	Requires(sensorSubsystem);
}

// Called just before this Command runs the first time
void SensorValueDisplayCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void SensorValueDisplayCommand::Execute() {
	SmartDashboard *sd = oi->getSmartDashboard();
	
	sd->PutDouble("Rangefinder dist (in)", sensorSubsystem->GetRangefinderDistanceInInches());
	
	sd->PutBoolean("Ball S1", sensorSubsystem->IsBallPresentSensor1());
	sd->PutBoolean("Ball S2", sensorSubsystem->IsBallPresentSensor2());
	sd->PutBoolean("Ball S3", sensorSubsystem->IsBallPresentSensor3());
	
	sd->PutBoolean("Arm Down", sensorSubsystem->IsArmDown());
	
	//printf("Yaw gyro angle %f\n", sensorSubsystem->GetYawGyroAngle());
	sd->PutDouble("Yaw gyro angle", sensorSubsystem->GetYawGyroAngle());	
	sd->PutDouble("Pitch gyro angle", sensorSubsystem->GetPitchGyroAngle());
	
	//printf("Sensors: 1:%d 2:%d 3:%d\n", sensorSubsystem->IsBallPresentSensor1(), 
	//		sensorSubsystem->IsBallPresentSensor2(), sensorSubsystem->IsBallPresentSensor3());
}

// Make this return true when this Command no longer needs to run execute()
bool SensorValueDisplayCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void SensorValueDisplayCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SensorValueDisplayCommand::Interrupted() {
}
