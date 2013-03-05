#include "FrisbeePanSupervisorCommand.h"
#include <math.h>

// Max value on counter for tilt
#define TILT_MAX_COUNT	300

// Setpoint for frisbee ingest tilt
#define INGEST_TILT_COUNT	130

// Setpoint for loading station tilt
#define LOAD_TILT_COUNT		160

// Setpoint for stowed tilt
#define	STOW_TILT_COUNT		280

// Range around goal value for ingest where we'll consider it "on target"
#define	INGEST_TOLERANCE		5

// Range around setpoint for tilt where we'll consider it "on target"
#define	TILT_TOLERANCE			10

//Time to wait after frisbee detect stops detecting frisbee on ingest before we lower
#define	INGEST_AFTER_SWITCH_TIME	(.10)

// PID tuning values
#define	P_GAIN	(-.006)
#define I_GAIN	(-.0004)

// The pan is lowered in two power levels;  the first is to get it started from the top,
// and the second is to get it down below the top.
#define	PAN_LOWER_POWER_PHASE1	(.25)

// Resist lowering a bit on the second phase to reduce banging of the pan on the ground.
#define	PAN_LOWER_POWER_PHASE2	(-.2)

// This is the count at which we transition from the phase1 to the
// phase 2 power level
#define PAN_LOWER_TRANSITION_COUNT	100

FrisbeePanSupervisorCommand::FrisbeePanSupervisorCommand() {
	Requires(frisbeePanSubsystem);
	this->controller = new PIDController(0, 0, 0,
			sensorSubsystem->GetPanLiftEncoder(), frisbeePanSubsystem->GetLiftMotor());
	this->controller->SetInputRange(0, TILT_MAX_COUNT);
	this->controller->SetOutputRange(-1, 1);
	this->controller->SetPID(P_GAIN, I_GAIN, 0);
	this->ingestTimer = new Timer();
}

// Called just before this Command runs the first time
void FrisbeePanSupervisorCommand::Initialize() {
	printf("FrisbeePanSupervisorCommand: initialize\n");
	frisbeePanSubsystem->SetMode(FrisbeePanSubsystem::EnteringCalibration);
	printf("FrisbeePanSupervisorCommand: initialized\n");
}

// Called repeatedly when this Command is scheduled to run
void FrisbeePanSupervisorCommand::Execute() {
	switch (frisbeePanSubsystem->GetMode())
	{
	case FrisbeePanSubsystem::EnteringCalibration:
		printf("FrisbeePanSupervisorCommand: EnteringCalibration\n");
		this->controller->Disable();
		frisbeePanSubsystem->StopIntake();

		this->initialCalibrationCount = sensorSubsystem->GetPanLiftEncoderCount();
		
		frisbeePanSubsystem->SetMode(FrisbeePanSubsystem::Calibrating);
		break;
		
	case FrisbeePanSubsystem::Calibrating:
		printf("FrisbeePanSupervisorCommand: Calibrating\n");
		if (sensorSubsystem->IsLoaderAtLowLimit())
		{
			frisbeePanSubsystem->GetLiftMotor()->Set(0);
			
			sensorSubsystem->GetPanLiftEncoder()->Reset();
			sensorSubsystem->GetPanLiftEncoder()->Start();
			frisbeePanSubsystem->SetMode(FrisbeePanSubsystem::Pickup);
		}
		else
		{
			int currentDifference = this->initialCalibrationCount - sensorSubsystem->GetPanLiftEncoderCount();
			if (currentDifference > PAN_LOWER_TRANSITION_COUNT)
			{
				printf("Lower 2 %d\n", currentDifference);
				frisbeePanSubsystem->GetLiftMotor()->Set(PAN_LOWER_POWER_PHASE2);
			}
			else
			{
				printf("Lower 1 %d\n", currentDifference);
				frisbeePanSubsystem->GetLiftMotor()->Set(PAN_LOWER_POWER_PHASE1);
			}
		}
		break;
		
	case FrisbeePanSubsystem::Ingest:
		printf("FrisbeePanSupervisorCommand: ingesting\n");

		if (!this->controller->IsEnabled())
		{
			this->controller->Reset();
			this->controller->SetSetpoint(INGEST_TILT_COUNT);
			this->controller->Enable();
		}
		else
		{
			if (sensorSubsystem->IsFrisbeeInLoader())
			{
				if (this->OnTarget(this->controller->GetSetpoint(), INGEST_TILT_COUNT, INGEST_TOLERANCE))
				{
					frisbeePanSubsystem->RunIntake();
				}
				else
				{
					printf("Waiting for tilt to be on target\n");
				}
			}
			else
			{
				// Frisbee has advanced past loader.  We will
				// wait a defined time after that for frisbee to get into robot, then
				// return to pickup mode.
				
				double currentTime = this->ingestTimer->Get();
				if (currentTime == 0)
				{
					// Timer isn't running
					this->ingestTimer->Start();
				}
				else if (currentTime > INGEST_AFTER_SWITCH_TIME)
				{
					this->ingestTimer->Stop();
					this->ingestTimer->Reset();
					this->controller->Disable();
					frisbeePanSubsystem->SetMode(FrisbeePanSubsystem::Pickup);
				}
				frisbeePanSubsystem->RunIntake();
			}
		}
		SmartDashboard::PutNumber("Ingest Tilt Power", this->controller->Get());
		SmartDashboard::PutBoolean("Ingest Tilt on target", this->controller->OnTarget());
		break;
	case FrisbeePanSubsystem::Load:
		printf("FrisbeePanSupervisorCommand: Load\n");
		this->controller->Reset();
		this->controller->SetSetpoint(LOAD_TILT_COUNT);
		this->controller->Enable();
		
		frisbeePanSubsystem->RunIntake();
		frisbeePanSubsystem->SetMode(FrisbeePanSubsystem::RunLoad);
		
		SmartDashboard::PutNumber("Ingest Tilt Power", this->controller->Get());
		break;
	case FrisbeePanSubsystem::RunLoad:
		printf("FrisbeePanSupervisorCommand: RunLoad\n");
		SmartDashboard::PutNumber("Ingest Tilt Power", this->controller->Get());
		break;
	case FrisbeePanSubsystem::ExitLoad:
		// Command can be pushed into this state externally to get 
		// us to exit the loading mode and return to pickup mode.
		printf("FrisbeePanSupervisorCommand: ExitLoad\n");
		
		this->controller->Reset();
		frisbeePanSubsystem->StopIntake();
		
		frisbeePanSubsystem->SetMode(FrisbeePanSubsystem::Pickup);
		break;
	case FrisbeePanSubsystem::Stow:
		printf("FrisbeePanSupervisorCommand: Stow\n");
		this->controller->Reset();
		this->controller->SetSetpoint(STOW_TILT_COUNT);
		this->controller->Enable();
		frisbeePanSubsystem->SetMode(FrisbeePanSubsystem::RunStow);
		break;
		
	case FrisbeePanSubsystem::RunStow:
		// Do nothing -- wait for another command to come along
		break;

	case FrisbeePanSubsystem::Pickup:
		this->controller->Reset();
		
		if (sensorSubsystem->IsFrisbeeInLoader())
		{
			frisbeePanSubsystem->StopIntake();
			frisbeePanSubsystem->SetMode(FrisbeePanSubsystem::Ingest);
		}
		else
		{
			frisbeePanSubsystem->RunIntake();
		}
		printf("FrisbeePanSupervisorCommand: pickup\n");
		break;
	default:
		printf("Unknown frisbee pan state; transitioning to Pickup\n");
		frisbeePanSubsystem->SetMode(FrisbeePanSubsystem::Pickup);
		break;
	}
}

bool FrisbeePanSupervisorCommand::OnTarget(float setpoint, float currentValue, float tolerance)
{
	printf("setpoint: %f; currentValue: %f; tolerannce: %f\n", setpoint, currentValue, tolerance);
	float difference = setpoint - currentValue;
	if (difference > 0)
	{
		return difference <= tolerance;
	}
	else if (difference < 0)
	{
		return -difference <= tolerance;
	}
	else
	{
		return true;
	}

}

bool FrisbeePanSupervisorCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void FrisbeePanSupervisorCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FrisbeePanSupervisorCommand::Interrupted() {

}
