#include "VisionTargetingCommandGroup.h"
#include "TurnSpecifiedDegreesPIDCommand.h"
#include "SetShooterTiltCommand.h"
#include "ShootFrisbeeAndIndexCommand.h"

VisionTargetingCommandGroup::VisionTargetingCommandGroup() {
	this->processVision = new ProcessVisionCommand();
	AddSequential(processVision);
	AddSequential(new TurnSpecifiedDegreesPIDCommand(processVision->GetAzimuth()));
	AddSequential(new SetShooterTiltCommand(processVision->GetTiltAngle()));
	
	double delay = 3.0;
	AddSequential(new WaitCommand(delay));
	AddSequential(new ShootFrisbeeAndIndexCommand());
}
