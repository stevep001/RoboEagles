#include "ShooterTiltSupervisorCommand.h"

#define TILT_COUNTS_PER_REVOLUTION	(1024)
#define	TILT_MAX_REVOLUTIONS		(1.25)
#define	TILT_MAX_COUNT				(TILT_COUNTS_PER_REVOLUTION * TILT_MAX_REVOLUTIONS)
#define	TILT_DEGREES_PER_REVOLUTION	(50)

// Max time to run initialization before giving up
#define	TILT_INITIALIZATION_TIMEOUT_SECS	(3)

#define TILT_UP_POWER	(.8)
#define	TILT_DOWN_POWER	(.3)

ShooterTiltSupervisorCommand::ShooterTiltSupervisorCommand() {
	Requires(shooterTiltSubsystem);
	this->initializationTimer = new Timer();
}

// Called just before this Command runs the first time
void ShooterTiltSupervisorCommand::Initialize() {
	printf("ShooterTiltSupervisorCommand: initialize\n");
	float pGain = -.035;
	float iGain = -.004;
	float dGain = 0; 

	this->controller = new PIDController(pGain, iGain, dGain, 
			sensorSubsystem->GetTiltEncoder(), shooterTiltSubsystem->GetMotor());
	
	this->controller->SetInputRange(0, TILT_MAX_COUNT);
	this->controller->SetOutputRange(-(TILT_UP_POWER), TILT_DOWN_POWER);
	
	this->initializationTimer->Stop();
	this->initializationTimer->Reset();
	this->initializationTimer->Start();
	shooterTiltSubsystem->SetMode(ShooterTiltSubsystem::Initializing);

	printf("ShooterTiltSupervisorCommand: initialize completed\n");
}

// Called repeatedly when this Command is scheduled to run
void ShooterTiltSupervisorCommand::Execute() {
	switch (this->shooterTiltSubsystem->GetMode())
	{
	case ShooterTiltSubsystem::Initializing:
		if (sensorSubsystem->GetTiltLowerLimit())
		{
			shooterTiltSubsystem->GetMotor()->Set(0);
			shooterTiltSubsystem->SetAngle(0);

			this->controller->SetSetpoint(0);
			this->controller->Reset();
			this->controller->Enable();
			this->shooterTiltSubsystem->SetMode(ShooterTiltSubsystem::Running);
			this->initializationTimer->Stop();

			printf("ShooterTiltSupervisorCommand:  tilt initialized\n");
		}
		else
		{
			if (initializationTimer->Get() < TILT_INITIALIZATION_TIMEOUT_SECS)
			{
				shooterTiltSubsystem->GetMotor()->Set(TILT_DOWN_POWER);
			}
			else
			{
				shooterTiltSubsystem->GetMotor()->Set(0);
				this->shooterTiltSubsystem->SetMode(ShooterTiltSubsystem::CalibrationError);
				printf("ShooterTiltSupervisorCommand: disabling: initialization didn't complete in time\n");
				// TODO: This might be a bit picky
			}
		}
		break;
	case ShooterTiltSubsystem::Running:
		if (sensorSubsystem->GetTiltLowerLimit() && shooterTiltSubsystem->GetAngle() == MIN_TILT_ANGLE)
		{
			if (this->controller->IsEnabled())
			{
				printf("ShooterTiltSupervisorCommand: calling for 0 and at low limit, resetting and disabling\n");
				this->controller->Reset();
			}
			
			// TODO: We could test here to see if PID loop thinks we're at low limit without limit switch.
		}
		else if (sensorSubsystem->GetTiltUpperLimit())
		{
			this->controller->Disable();
			printf("ShooterTiltSupervisorCommand: disabling: high limit\n");
			this->shooterTiltSubsystem->SetMode(ShooterTiltSubsystem::HighLimitError);
		}
		else
		{
			if (!this->controller->IsEnabled()) {
				printf("ShooterTiltSupervisorCommand: enabling\n");
				this->controller->Enable();
			}
		}
		break;
	case ShooterTiltSubsystem::CalibrationError:
		// Do nothing
		break;
	default:
		printf("ShooterTiltSupervisorCommand:  Unknown mode %d; setting to Initializing", this->shooterTiltSubsystem->GetMode());
		this->shooterTiltSubsystem->SetMode(ShooterTiltSubsystem::Initializing);
		break;
	}
	
	float setpoint = (shooterTiltSubsystem->GetAngle() / TILT_DEGREES_PER_REVOLUTION) * TILT_COUNTS_PER_REVOLUTION;
	if (setpoint > TILT_MAX_COUNT)
	{
		setpoint = TILT_MAX_COUNT;
	}
	this->controller->SetSetpoint(setpoint);
	SmartDashboard::PutNumber("Tilt setpoint", setpoint);
	SmartDashboard::PutNumber("Tilt PID output", this->controller->Get());

}


// Make this return true when this Command no longer needs to run execute()
bool ShooterTiltSupervisorCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ShooterTiltSupervisorCommand::End() {
	this->Cleanup();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterTiltSupervisorCommand::Interrupted() {
	this->Cleanup();
}

void ShooterTiltSupervisorCommand::Cleanup() {
	if (this->controller != NULL)
	{
		this->controller->Disable();
		delete this->controller;
		this->controller = NULL;
	}
}
