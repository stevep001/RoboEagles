#include "PIDDriveommand.h"

PIDDriveommand::PIDDriveommand(float inches) {
	Requires(chassis);
	this->distance = inches;
}
PIDDriveommand::PIDDriveommand(int feet, int inches, bool forward) {
	double distanceUnsigned = (feet * 12) + inches;
	if(!forward) {
		distanceUnsigned = -distanceUnsigned;
	}
	this->distance = distanceUnsigned;
}
// Called just before this Command runs the first time
void PIDDriveommand::Initialize() {
	sensorSubsystem->GetLeftDriveEncoder()->Reset();
	sensorSubsystem->GetRightDriveEncoder()->Reset();

	float range =  this->distance * (TICKS_ENCODER * (TEETH_DRIVE / TEETH_WHEEL));
	float setpoint = this->distance * (TICKS_ENCODER * (TEETH_DRIVE / TEETH_WHEEL));
	float tolerance = 2 * (TICKS_ENCODER * (TEETH_DRIVE / TEETH_WHEEL));
	
	float leftPGain 		= 0;
	float leftIGain 		= 0;
	float leftDGain 		= 0;
	float leftFeedForward	= 0;
	
	this->leftController = new PIDController(leftPGain,leftIGain,leftDGain,leftFeedForward,sensorSubsystem->GetLeftDriveEncoder(), chassis->GetLeftMotor());
	this->leftController->SetInputRange(-range, range);
	this->leftController->SetOutputRange(-1.0,1.0);
	this->leftController->SetAbsoluteTolerance(tolerance);
	this->leftController->Reset();
	this->leftController->SetSetpoint(setpoint);
	
	float rightPGain		= 0;
	float rightIGain		= 0;
	float rightDGain		= 0;
	float rightFeedForward	= 0;
	
	this->rightController = new PIDController(rightPGain, rightIGain, rightDGain, rightFeedForward, sensorSubsystem->GetRightDriveEncoder(), chassis->GetRightMotor());
	this->rightController->SetInputRange(-range, range);
	this->rightController->SetOutputRange(-1, 1);
	this->rightController->SetAbsoluteTolerance(tolerance);
	this->rightController->Reset();
	this->rightController->SetSetpoint(setpoint);
	
	this->leftController->Enable();
	this->rightController->Enable();
}

// Called repeatedly when this Command is scheduled to run
void PIDDriveommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool PIDDriveommand::IsFinished() {
	return this->leftController->OnTarget() && this->rightController->OnTarget();
}

// Called once after isFinished returns true
void PIDDriveommand::End() {
	this->cleanUp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PIDDriveommand::Interrupted() {
	this->cleanUp();
}

void PIDDriveommand::cleanUp() {
	if(this->leftController != NULL) {
		this->leftController->Disable();
		delete this->leftController;
		this->leftController = NULL;
	}
	if(this->rightController != NULL) {
		this->rightController->Disable();
		delete this->rightController;
		this->rightController = NULL;
	}
}
