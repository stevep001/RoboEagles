#include "LifterManualCommand.h"
#include "../Robotmap.h"

LifterManualCommand::LifterManualCommand() : CommandBase("LifterManualCommand"){
	Requires(lifterSubsystem);
}

void LifterManualCommand::Initialize() {
	
}

void LifterManualCommand::Execute() {
	double LiftD = oi->getLiftJoystick()->GetRawButton(LIFT_DOWN_BUTTON);
	double LiftU = oi->getLiftJoystick()->GetRawButton(LIFT_UP_BUTTON);
	if (LiftU){
		oi->getSmartDashboard()->PutString("Lift", "going up");
		lifterSubsystem->LiftUp();
	}
	else if (LiftD){
		oi->getSmartDashboard()->PutString("Lift", "going down");
		lifterSubsystem->LiftDown();
	}

	else {
		oi->getSmartDashboard()->PutString("Lift", "stopped");
		lifterSubsystem->LiftStop();
	}
	
}

// Make this return true when this Command no longer needs to run execute()
bool LifterManualCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void LifterManualCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LifterManualCommand::Interrupted() {
}
