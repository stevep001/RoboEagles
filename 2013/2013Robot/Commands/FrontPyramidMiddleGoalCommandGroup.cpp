#include "FrontPyramidMiddleGoalCommandGroup.h"
#include "SetShooterTiltCommand.h"
#include "ShootFrisbeeAndIndexCommand.h"

FrontPyramidMiddleGoalCommandGroup::FrontPyramidMiddleGoalCommandGroup() {
	printf("[FrontPyramidMiddleGoalCommandGroup] Constructing\n");
	AddSequential(new SetShooterTiltCommand(30));
	AddSequential(new WaitCommand(3));
	AddSequential(new ShootFrisbeeAndIndexCommand());
	printf("[FrontPyramidMiddleGoalCommandGroup] Constructed\n");
}
