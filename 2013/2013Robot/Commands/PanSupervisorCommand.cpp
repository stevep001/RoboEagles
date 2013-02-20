#include "PanSupervisorCommand.h"

#define		PAN_INGEST_BELT_SPEED		(.4)
#define		PAN_LATERAL_BELT_SPEED		(.4)

PanSupervisorCommand::PanSupervisorCommand() {
	Requires(panSubsystem);
}

// Called just before this Command runs the first time
void PanSupervisorCommand::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void PanSupervisorCommand::Execute() {
	panSubsystem->SetIngestBeltSpeed(PAN_INGEST_BELT_SPEED);
	panSubsystem->SetLateralBeltSpeed(PAN_LATERAL_BELT_SPEED);
}

// Make this return true when this Command no longer needs to run execute()
bool PanSupervisorCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void PanSupervisorCommand::End() {
	panSubsystem->SetIngestBeltSpeed(0);
	panSubsystem->SetLateralBeltSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PanSupervisorCommand::Interrupted() {
	panSubsystem->SetIngestBeltSpeed(0);
	panSubsystem->SetLateralBeltSpeed(0);
}
