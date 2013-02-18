#include "SensorDisplayCommand.h"
#include "../Subsystems/SensorSubsystem.h"

SensorDisplayCommand::SensorDisplayCommand() {
	Requires(sensorSubsystem);
}

// Called just before this Command runs the first time
void SensorDisplayCommand::Initialize() {
	printf("SensorDisplayCommand:  Initialized\n");
}

// Called repeatedly when this Command is scheduled to run
void SensorDisplayCommand::Execute() {
	// Tilt
	SmartDashboard::PutBoolean("Tilt Encoder MagDec", sensorSubsystem->GetTiltEncoderMagDec());
	SmartDashboard::PutBoolean("Tilt Encoder MagInc", sensorSubsystem->GetTiltEncoderMagInc());
	SmartDashboard::PutBoolean("Tilt upper", sensorSubsystem->GetTiltUpperLimit());
	SmartDashboard::PutBoolean("Tilt lower", sensorSubsystem->GetTiltLowerLimit());
	SmartDashboard::PutNumber("Tilt", sensorSubsystem->GetTiltEncoderValue());
	
	// Pizza box
	SmartDashboard::PutBoolean("Kicker", sensorSubsystem->GetKickerLimitSwitch());
	SmartDashboard::PutBoolean("Pizza box top", sensorSubsystem->GetPizzaTopLimitSwitch());
	SmartDashboard::PutBoolean("Pizza box bottom", sensorSubsystem->GetPizzaBottomLimitSwitch());
	SmartDashboard::PutBoolean("Pizza box upper", sensorSubsystem->GetPizzaUpperLimitSwitch());
	SmartDashboard::PutBoolean("Pizza box lower", sensorSubsystem->GetPizzaLowerLimitSwitch());

	// Shooter
	// Checking to see whether this fixes reading encoder value in subsystem
	//SmartDashboard::PutNumber("Shooter encoder", sensorSubsystem->GetShooterEncoderValue());
	
	// Chassis
	SmartDashboard::PutNumber("Left drive", sensorSubsystem->GetLeftEncoderValue());
	SmartDashboard::PutNumber("Right drive", sensorSubsystem->GetRightEncoderValue());
	
	// Gyro
	
	SmartDashboard::PutNumber("Gyro heading", sensorSubsystem->GetHorizontalAngle());
	
	// Kicker
	SmartDashboard::PutBoolean("Kicker", sensorSubsystem->GetKickerLimitSwitch());
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
