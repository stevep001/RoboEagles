#include "SensorDisplayCommand.h"

SensorDisplayCommand::SensorDisplayCommand() {
	Requires(sensorSubsystem);
}

// Called just before this Command runs the first time
void SensorDisplayCommand::Initialize() {
	printf("SensorDisplayCommand initialized\n");
}

// Called repeatedly when this Command is scheduled to run
void SensorDisplayCommand::Execute() {
	SmartDashboard::PutBoolean("Frisbee in loader", sensorSubsystem->IsFrisbeeInLoader());
	SmartDashboard::PutBoolean("Loader is at low limit", sensorSubsystem->IsLoaderAtLowLimit());
	SmartDashboard::PutNumber("Pan lift encoder", sensorSubsystem->GetPanLiftEncoderCount());
	// TODO try this when present 
	//SmartDashboard::PutBoolean("DS Digital input 1", DriverStation::GetInstance()->GetDigitalIn(1));
}

// Make this return true when this Command no longer needs to run execute()
bool SensorDisplayCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void SensorDisplayCommand::End() {
	printf("SensorDisplayCommand end\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SensorDisplayCommand::Interrupted() {
	printf("SensorDisplayCommand interrupted\n");

}
