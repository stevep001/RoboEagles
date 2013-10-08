#include "TurnSpecifiedDegreesPIDCommand.h"

TurnSpecifiedDegreesPIDCommand::TurnSpecifiedDegreesPIDCommand(float degrees) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	printf("[TurnSpecifiedDegreesPIDCommand] Starting construction\n");
	Requires(chassis);
	this->setPoint = degrees;
	printf("[TurnSpecifiedDegreesPIDCommand] Has constructed\n");
}

// Called just before this Command runs the first time
void TurnSpecifiedDegreesPIDCommand::Initialize() {
	printf("[TurnSpecifiedDegreesPIDCommand] Reseting Gyro\n");
	sensorSubsystem->GetHorizontalGyro()->Reset();
	
	this->pGain = 0.06;
	this->iGain = 0.0;
	this->dGain = 0.0;
	this->feedforward = 0.0;
	
	this->pidOutput = new DrivetrainPIDOutput(chassis->GetRobotDrive());
	printf("[TurnSpecifiedDegreesPIDCommand] Ccreating new Pid controller with P:%f,I:%f,D:%f\n",pGain,iGain,dGain);
	this->controller = new PIDController(pGain, iGain, dGain, feedforward, sensorSubsystem->GetHorizontalGyro(), this);
	
	this->pidGyroMin = -180.0;
	this->pidGyroMax = 180.0;
	this->controller->SetInputRange(pidGyroMin, pidGyroMax);
	this->controller->SetOutputRange(-1.0, 1.0);
	
	printf("[TurnSpecifiedDegreesPIDCommand] The PID controller set point is %f\n", setPoint);
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
	printf("[TurnSpecifiedDegreesPIDCommand] Is going to end\n");
	this->cleanUp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnSpecifiedDegreesPIDCommand::Interrupted() {
	printf("[TurnSpecifiedDegreesPIDCommand] Has Been Interrupted\n");
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

void TurnSpecifiedDegreesPIDCommand::PIDWrite(float output) {
	chassis->GetRobotDrive()->TankDrive(-output, output);
}
