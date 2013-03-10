#include "ShooterSupervisorCommand.h"
#include "../RpmSource.h"

#define NORMAL_POWER	(5500)
#define LOFT_POWER		(4200)
#define TEST_POWER		(2000)

ShooterSupervisorCommand::ShooterSupervisorCommand() {
	printf("ShooterSupervisorCommand: constructing\n");
	Requires(shooterSubsystem);
	this->rpmSource = new RpmSource();
	this->timer = new Timer();
	printf("ShooterSupervisorCommand: constructed\n");
}

ShooterSupervisorCommand::~ShooterSupervisorCommand() {
	this->Cleanup();
}

// Called just before this Command runs the first time
void ShooterSupervisorCommand::Initialize() {
	printf("ShooterSupervisorCommand: initialize\n");
	// PID tuning parameters
	float pGain = .001;
	float iGain = .0001;
	float dGain = 0;
	float feedForwardValue = .0002;
	
	float rpmMaximum = 5500;	
	this->controller = new PIDController(pGain, iGain, dGain, feedForwardValue, rpmSource, shooterSubsystem->GetMotor());
	this->controller->SetInputRange(-rpmMaximum, rpmMaximum);
	this->controller->SetOutputRange(-1, 1);

	this->timer->Reset();
	this->timer->Start();
	this->lastTime = timer->Get();
	this->lastCountEncoder1 = sensorSubsystem->GetShooterEncoder1Value();
//	this->lastCountEncoder2 = sensorSubsystem->GetShooterEncoder2Value();
	
	controller->SetSetpoint(- NORMAL_POWER);
//	controller->SetSetpoint(-5000);
//	controller->SetSetpoint(-4200);		// This is a good setting for lofting frisbees into the pyramid
	controller->Enable();
	printf("ShooterSupervisorCommand: initialize completed\n");
}

void ShooterSupervisorCommand::Execute() {
	double countsPerRevolution = 200;

	double currentTime = timer->Get();
	double timeDifference = currentTime - lastTime;
	lastTime = currentTime;
	
	int currentCount = sensorSubsystem->GetShooterEncoder1Value();
	int countDifference = currentCount - lastCountEncoder1;
	lastCountEncoder1 = currentCount;

	double rpm = countDifference * (60.0 / countsPerRevolution) / timeDifference;
	rpmSource->inputRpm(rpm);

	switch (shooterSubsystem->GetShootingPower())
	{
	case ShooterSubsystem::Low:
		controller->SetSetpoint(- LOFT_POWER);
		break;
	case ShooterSubsystem::Test:
		controller->SetSetpoint(- TEST_POWER);
		break;
	case ShooterSubsystem::Normal:
	default:
		controller->SetSetpoint(- NORMAL_POWER);
		break;
	}
	
	//printf("RPM %f count %d; difference %d; timeDifference %f\n", rpm, currentCount, countDifference, timeDifference);
	
	//printf("setpoint %f RPM %f result %f error %f \n", controller->GetSetpoint(), rpm, controller->Get(), controller->GetError());
	SmartDashboard::PutNumber("Shooter RPM", rpm);
	SmartDashboard::PutNumber("Count Difference", countDifference);
	SmartDashboard::PutNumber("Current count", currentCount);
	SmartDashboard::PutNumber("Time difference", timeDifference);
	SmartDashboard::PutNumber("Motor speed", shooterSubsystem->GetMotor()->Get());
	
	SmartDashboard::PutNumber("PID target", this->controller->Get());

//	int currentCount2 = sensorSubsystem->GetShooterEncoder2Value();
//	int countDifference2 = currentCount2 - lastCountEncoder2;
//	lastCountEncoder2 = currentCount2;
//
//	SmartDashboard::PutNumber("Encoder 2 difference", countDifference2);
	
	if (pizzaBoxSubsystem->FiringSoon())
	{
		controller->Enable();
	}
	else
	{
		controller->Disable();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterSupervisorCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ShooterSupervisorCommand::End() {
	this->Cleanup();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterSupervisorCommand::Interrupted() {
	this->Cleanup();
}

void ShooterSupervisorCommand::Cleanup()
{
	if (timer != NULL)
		timer->Stop();
	
	if (controller != NULL)
	{
		controller->Disable();
		delete controller;
		controller = NULL;
	}	
}
