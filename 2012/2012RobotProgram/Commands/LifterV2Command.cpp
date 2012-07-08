#include "LifterV2Command.h"

LifterV2Command::LifterV2Command(lifter_mode mode) : CommandBase("LifterV2Command") {
	desiredMode = mode;
	Requires(lifterSubsystem);
	}

void LifterV2Command::Initialize() {
	if (desiredMode == UP){
		oi->getSmartDashboard()->PutString("Lift", "going up");
		lifterSubsystem->LiftUp();
	}
	else if (desiredMode == DOWN){
		oi->getSmartDashboard()->PutString("Lift", "going down");
		lifterSubsystem->LiftDown();
	}
	else {
		oi->getSmartDashboard()->PutString("Lift", "stopped");
		lifterSubsystem->LiftStop();
	}
}

void LifterV2Command::Execute() {
}

bool LifterV2Command::IsFinished() {
	return true;
}

void LifterV2Command::End() {
}

void LifterV2Command::Interrupted() {
}
