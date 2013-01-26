#include "PositionHoldingCommand.h"

PositionHoldingCommand::PositionHoldingCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(prototypingsubsystem);

}

PositionHoldingCommand::~PositionHoldingCommand()
{
	if (controller != NULL)
	{
		controller->Disable();
		delete controller;
		controller = NULL;
	}
}

// Called just before this Command runs the first time
void PositionHoldingCommand::Initialize() {
	float pGain = .0013;
	float iGain = .0002;
	float dGain = 0;
	Encoder *encoder = prototypingsubsystem->GetMotorEncoder();
	encoder->SetPIDSourceParameter(Encoder::kDistance);
	printf("Before new\n");
	controller = new PIDController(pGain, iGain, dGain, 
			prototypingsubsystem->GetMotorEncoder(), prototypingsubsystem->GetMotor());
	printf("after new\n");
	controller->SetInputRange(-500, 500);
	controller->SetOutputRange(-1, 1);
	controller->Enable(); // start calculating PIDOutput values
	controller->SetSetpoint(100);
	printf("Initialized\n");
}

// Called repeatedly when this Command is scheduled to run
void PositionHoldingCommand::Execute() {
	oi->DisplayEncoder(prototypingsubsystem->GetMotorEncoder());
	oi->DisplayPIDController(controller);
	printf("setpoint %f result %f error%f \n", controller->GetSetpoint(), controller->Get(), controller->GetError());
}

// Make this return true when this Command no longer needs to run execute()
bool PositionHoldingCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void PositionHoldingCommand::End() {
	if (controller != NULL)
	{
		controller->Disable();
		delete controller;
		controller = NULL;
	}
	printf("en\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PositionHoldingCommand::Interrupted() {
	if (controller != NULL)
	{
		controller->Disable();
		delete controller;
		controller = NULL;
	}
	printf("interrupted\n");
}
