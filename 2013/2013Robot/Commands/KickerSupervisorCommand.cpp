#include "KickerSupervisorCommand.h"

#define	MOTOR_SPEED	.76

KickerSupervisorCommand::KickerSupervisorCommand() {
	Requires(kickerSubsystem);
}

void KickerSupervisorCommand::Initialize() {
	
}

void KickerSupervisorCommand::Execute() {
	switch (kickerSubsystem->GetKickerState())
	{
	case KickerSubsystem::Initializing:
		if (sensorSubsystem->IsKickerStowed())
		{
			kickerSubsystem->SetKickerState(KickerSubsystem::Stowed);
			this->StopMotor();
			printf("KickerSupervisorCommand: kicker position initialized\n");
		}
		else
		{
			kickerSubsystem->SetKickerState(KickerSubsystem::KickingWaitingForSwitchOn);
			this->RunMotor();
			printf("KickerSupervisorCommand: initializing kicker position\n");		}
		break;
	case KickerSubsystem::Stowed:
		// Do nothing
		break;
	case KickerSubsystem::KickingWaitingForSwitchOff:
		this->RunMotor();
		if (!sensorSubsystem->IsKickerStowed())
		{
			kickerSubsystem->SetKickerState(KickerSubsystem::KickingWaitingForSwitchOn);
			printf("KickerSupervisorCommand: waiting for switch on\n");
		}
		break;
	case KickerSubsystem::KickingWaitingForSwitchOn:
		if (sensorSubsystem->IsKickerStowed())
		{
			this->StopMotor();
			kickerSubsystem->SetKickerState(KickerSubsystem::Stowed);
			printf("KickerSupervisorCommand: kicker stowed\n");
		}
		else
		{
			this->RunMotor();
		}
		break;
	default:
		printf("KickerSupervisorCommand: unknown state %d; resetting to Initializing\n", kickerSubsystem->GetKickerState());
		kickerSubsystem->SetKickerState(KickerSubsystem::Initializing);
		break;
	}
}

void KickerSupervisorCommand::StopMotor()
{
	kickerSubsystem->SetSpeed(0);
}

void KickerSupervisorCommand::RunMotor()
{
	kickerSubsystem->SetSpeed(MOTOR_SPEED);
}

// Make this return true when this Command no longer needs to run execute()
bool KickerSupervisorCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void KickerSupervisorCommand::End() {
	printf("KickerSupervisorCommand: End\n");
	this->StopMotor();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void KickerSupervisorCommand::Interrupted() {
	printf("KickerSupervisorCommand: Interrupted\n");
	this->StopMotor();
}
