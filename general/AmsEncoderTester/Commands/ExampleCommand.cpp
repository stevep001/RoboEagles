#include "ExampleCommand.h"

ExampleCommand::ExampleCommand() {
	// Use Requires() here to declare subsystem dependencies
	Requires(examplesubsystem);
	this->timer = new Timer();
}

// Called just before this Command runs the first time
void ExampleCommand::Initialize() {
	printf("Example command starting\n");
	this->timer->Start();
	this->lastTime = this->timer->Get();
	this->lastCount = examplesubsystem->GetCount();
}

// Called repeatedly when this Command is scheduled to run
void ExampleCommand::Execute() {
	int currentCount = examplesubsystem->GetCount();
	double currentTime = timer->Get();
	
	// Supposedly 1024 pulses / 4096 ticks
	int deltaCount = currentCount - this->lastCount;
	double deltaTime = currentTime - this->lastTime;
	double rawRpm = deltaCount * (60.0 / 1024) / deltaTime;
	
	SmartDashboard::PutBoolean("magdec", examplesubsystem->GetMagDec());
	SmartDashboard::PutBoolean("magInc", examplesubsystem->GetMagInc());
	SmartDashboard::PutNumber("encoder count", currentCount);
	SmartDashboard::PutNumber("RPM", rawRpm);
	SmartDashboard::PutNumber("delta count", deltaCount);
	SmartDashboard::PutNumber("delta time", deltaTime);
	examplesubsystem->SetMotorPower(.8);
	
	this->lastCount = currentCount;
	this->lastTime = currentTime;
}

// Make this return true when this Command no longer needs to run execute()
bool ExampleCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ExampleCommand::End() {
	examplesubsystem->SetMotorPower(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExampleCommand::Interrupted() {
	examplesubsystem->SetMotorPower(0);
}
