#include "AutoRampBasketsCommandGroup.h"
#include "DriveStraightCommand.h"
#include "TurnSpecifiedDegreesCommand.h"
#include "LifterV2Command.h"
#include "LoadBallFromBeltIntoThrowerCommandGroup.h"
#include "ThrowerV2Command.h"
#include "LiftDownUntilTiltCommand.h"

/**
 * This implements a ramp then baskets autonomous mode.  Largely untested.
 */
AutoRampBasketsCommandGroup::AutoRampBasketsCommandGroup() {
	AddSequential(new PrintCommand("Starting AutoRampBasketsCommandGroup"));

	AddSequential(new PrintCommand("Driving to ramp"));
	AddSequential(new DriveStraightCommand(2, .5));
	
	AddSequential(new PrintCommand("Backing up from ramp"));
	AddSequential(new DriveStraightCommand(0.5, -.5));
	
	AddSequential(new PrintCommand("Lowering lifter"));
	AddSequential(new LiftDownUntilTiltCommand());

	AddSequential(new PrintCommand("Waiting for balls to move"));
	AddSequential(new WaitCommand(2));
		
	AddSequential(new PrintCommand("Moving lifter up"));
	AddSequential(new LifterV2Command(UP));

	AddSequential(new PrintCommand("Backing up after ball move"));
	AddSequential(new DriveStraightCommand(1, -.5));

	AddSequential(new PrintCommand("Turning"));
	AddSequential(new TurnSpecifiedDegreesCommand(180));

	AddSequential(new PrintCommand("Driving to throwing position"));
	AddSequential(new DriveStraightCommand(1, .5));
	
	AddSequential(new PrintCommand("Throwing"));
	AddSequential(new ThrowerV2Command(.2));
	AddSequential(new WaitCommand(1));
	
	AddSequential(new PrintCommand("Loading ball into thrower from belt"));
	AddSequential(new LoadBallFromBeltIntoThrowerCommandGroup());
	AddSequential(new WaitCommand(.2));
	
	AddSequential(new PrintCommand("Throwing"));
	AddSequential(new ThrowerV2Command(.2));
	
	AddSequential(new PrintCommand("Completing AutoRampBasketsCommandGroup"));	

}
