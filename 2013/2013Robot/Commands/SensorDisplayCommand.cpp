#include "SensorDisplayCommand.h"
#include "../Subsystems/SensorSubsystem.h"

SensorDisplayCommand::SensorDisplayCommand() {
	Requires(sensorSubsystem);
}

// Called just before this Command runs the first time
void SensorDisplayCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void SensorDisplayCommand::Execute() {
	SmartDashboard::PutBoolean("Tilt Encoder MagDec", sensorSubsystem->GetTiltEncoderMagDec());
	SmartDashboard::PutBoolean("Tilt Encoder MagInc", sensorSubsystem->GetTiltEncoderMagInc());
}

// Make this return true when this Command no longer needs to run execute()
bool SensorDisplayCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void SensorDisplayCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SensorDisplayCommand::Interrupted() {
}
