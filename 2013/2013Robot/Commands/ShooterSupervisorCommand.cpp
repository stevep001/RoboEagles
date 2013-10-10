#include "ShooterSupervisorCommand.h"
#include "../RpmSource.h"

#define NORMAL_POWER	(-0.96)
#define LOFT_POWER		(-0.86)
#define TEST_POWER		(-0.86)

ShooterSupervisorCommand::ShooterSupervisorCommand() {
	printf("ShooterSupervisorCommand: constructing\n");
	Requires(shooterSubsystem);
	printf("ShooterSupervisorCommand: constructed\n");
}

ShooterSupervisorCommand::~ShooterSupervisorCommand() {
	this->Cleanup();
}

// Called just before this Command runs the first time
void ShooterSupervisorCommand::Initialize() {
	printf("ShooterSupervisorCommand: initialize\n");
	m_speed = 0;
	printf("ShooterSupervisorCommand: initialize completed\n");
}

void ShooterSupervisorCommand::Execute() {
	switch (shooterSubsystem->GetShootingPower())
	{
	case ShooterSubsystem::Low:
		//controller->SetSetpoint(- LOFT_POWER);
		m_speed = LOFT_POWER;
		break;
	case ShooterSubsystem::Test:
		//controller->SetSetpoint(- TEST_POWER);
		m_speed = TEST_POWER;
		break;
	case ShooterSubsystem::Normal:
	default:
		//controller->SetSetpoint(- NORMAL_POWER);
		m_speed = NORMAL_POWER;
		break;
	}
	SmartDashboard::PutNumber("Shooter Motor speed", shooterSubsystem->GetMotor()->Get());
	
	if (pizzaBoxSubsystem->FiringSoon())
	{
		//controller->Enable();
		shooterSubsystem->GetMotor()->Set(m_speed);
	}
	else
	{
		//controller->Disable();
		shooterSubsystem->GetMotor()->Set(0);
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
	shooterSubsystem->GetMotor()->Set(0);	
}
