#include "TurnSpecifiedDegreesPIDCommand.h"

TurnSpecifiedDegreesPIDCommand::TurnSpecifiedDegreesPIDCommand(float degrees) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(chassis);
	this->setPoint = degrees;
}

// Called just before this Command runs the first time
void TurnSpecifiedDegreesPIDCommand::Initialize() {
	this->pGain = 0.0;
	this->iGain = 0.0;
	this->dGain = 0.0;
	this->feedforward = 0.0;
	
	this->pidOutput = new DrivetrainPIDOutput(chassis->GetRobotDrive());
	this->controller = new PIDController(pGain, iGain, dGain, feedforward, sensorSubsystem->GetHorizontalGyro(), this->pidOutput);
	
	this->pidGyroMin = -180.0;
	this->pidGyroMax = 180.0;
	this->controller->SetInputRange(pidGyroMin, pidGyroMax);
	this->controller->SetOutputRange(-1.0, 1.0);
	
	this->controller->SetSetpoint(setPoint);
	
	this->setPointTolerance = 2.0;
	this->controller->SetAbsoluteTolerance(setPointTolerance);
	
	this->controller->Enable();
}

// Called repeatedly when this Command is scheduled to run
void TurnSpecifiedDegreesPIDCommand::Execute() {
	SmartDashboard::PutNumber("PID Turning Error", this->controller->GetError());
}

// Make this return true when this Command no longer needs to run execute()
bool TurnSpecifiedDegreesPIDCommand::IsFinished() {
	return this->controller->OnTarget();
}

// Called once after isFinished returns true
void TurnSpecifiedDegreesPIDCommand::End() {
	this->cleanUp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnSpecifiedDegreesPIDCommand::Interrupted() {
	this->cleanUp();
}

void TurnSpecifiedDegreesPIDCommand::cleanUp() {
	if (this->controller != NULL)
	{
		this->controller->Disable();
		delete this->controller;
		this->controller = NULL;
	}
}
