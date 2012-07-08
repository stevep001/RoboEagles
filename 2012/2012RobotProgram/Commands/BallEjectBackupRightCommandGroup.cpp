#include "BallEjectBackupRightCommandGroup.h"

#include "DriveStraightCommand.h"
#include "TurnSpecifiedDegreesCommand.h"
#include "EjectBallsCommand.h"


BallEjectBackupRightCommandGroup::BallEjectBackupRightCommandGroup() {
	AddSequential(new PrintCommand("Starting AutoBasketsRampCommandGroup"));
	AddSequential(new EjectBallsCommand(10));
	
	AddSequential(new PrintCommand("Backing up"));
	AddSequential(new DriveStraightCommand(3, .6));
	
	AddSequential(new PrintCommand("Turning"));
	AddSequential(new TurnSpecifiedDegreesCommand(-90));

	AddSequential(new PrintCommand("Driving forward"));
	AddSequential(new DriveStraightCommand(3, -.6));
	}
