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
//	float pGain = -.035;
//	float iGain = -.003;
//	float dGain = 0;
	// Was: 0.002
	float pGain = .0025; // .0028, .0027,.0025
	float iGain = .0009; //was .0008, .0009
	float dGain = .0015;
	float feedForward = 0.0;

	this->controller = shooterTiltSubsystem->GetTiltPIDController();
	//this->controller = new PIDController(pGain, iGain, dGain, feedForward,
	//		sensorSubsystem->GetTiltEncoder(), shooterTiltSubsystem->GetMotor());
	//shooterTiltSubsystem->GetTiltPIDController()->Disable();
	this->controller->Disable();
	//shooterTiltSubsystem->GetTiltPIDController()->Reset();
	this->controller->Reset();
	//shooterTiltSubsystem->GetTiltPIDController()->SetPID(pGain, iGain, dGain, feedForward);
	this->controller->SetPID(pGain,iGain,dGain,feedForward);
	
	this->controller->SetInputRange(0, TILT_MAX_COUNT);
	//shooterTiltSubsystem->GetTiltPIDController()->SetInputRange(0, TILT_MAX_COUNT);
	
	this->controller->SetOutputRange(-1, 1);
	//shooterTiltSubsystem->GetTiltPIDController()->SetOutputRange(-1, 1);
	
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
			//shooterTiltSubsystem->GetTiltPIDController()->SetSetpoint(0);
			this->controller->Reset();
			//shooterTiltSubsystem->GetTiltPIDController()->Reset();
			this->controller->Enable();
			//shooterTiltSubsystem->GetTiltPIDController()->Enable();
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
			if (shooterTiltSubsystem->GetTiltPIDController()->IsEnabled())
			{
				printf("ShooterTiltSupervisorCommand: calling for 0 and at low limit, resetting and disabling\n");
				this->controller->Reset();
				//shooterTiltSubsystem->GetTiltPIDController()->Reset();
			}
			
			// TODO: We could test here to see if PID loop thinks we're at low limit without limit switch.
		}
		else if (sensorSubsystem->GetTiltUpperLimit())
		{
			this->controller->Disable();
			//shooterTiltSubsystem->GetTiltPIDController()->Disable();
			printf("ShooterTiltSupervisorCommand: disabling: high limit\n");
			this->shooterTiltSubsystem->SetMode(ShooterTiltSubsystem::HighLimitError);
		}
		else
		{
			if (!shooterTiltSubsystem->GetTiltPIDController()->IsEnabled()) {
				printf("ShooterTiltSupervisorCommand: enabling\n");
				this->controller->Enable();
				//shooterTiltSubsystem->GetTiltPIDController()->Enable();
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
	//shooterTiltSubsystem->GetTiltPIDController()->SetSetpoint(setpoint);
	SmartDashboard::PutNumber("Tilt setpoint", setpoint);
	//SmartDashboard::PutNumber("Tilt PID output", this->controller->Get());
	SmartDashboard::PutNumber("Tilt PID Output", this->controller->GetSetpoint());
	SmartDashboard::PutNumber("Tilt encoder output", shooterTiltSubsystem->GetTiltEncoder()->Get());
	float tiltError = setpoint - shooterTiltSubsystem->GetTiltEncoder()->Get();
	SmartDashboard::PutNumber("Tilt error", tiltError);
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
	this->controller->Disable();
	this->controller->Reset();
}
