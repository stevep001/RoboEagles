#include "FrontPyramidHighGoalCommandGroup.h"
#include "TurnSpecifiedDegreesPIDCommand.h"
#include "TurnSpecifiedDegreesCommand.h"
#include "SetShooterTiltCommand.h"
#include "ShootFrisbeeAndIndexCommand.h"

FrontPyramidHighGoalCommandGroup::FrontPyramidHighGoalCommandGroup(Side side) {
	printf("[FrontPyramidHighGoalCommandGroup] Constructing\n");
	double degrees = 0;
	if(side = kRight) {
		degrees = RIGHT_DEGREES_TO_TURN;
	} else if(side = kLeft) {
		degrees = LEFT_DEGREES_TO_TURN;
	}
	AddParallel(new TurnSpecifiedDegreesPIDCommand(degrees));
	//Uncomment this it the pid version doesnt work.
	//AddParallel(new TurnSpecifiedDegreesCommand(degrees));
	
	AddSequential(new SetShooterTiltCommand(28));
	
	double timeout = 3;
	AddSequential(new WaitCommand(timeout));
	
	AddSequential(new ShootFrisbeeAndIndexCommand());
	printf("[FrontPyramidHighGoalCommandGroup] Constructed\n");
}
