#include "AutoBasketsRampCommandGroup.h"
#include "DriveStraightCommand.h"
#include "TurnSpecifiedDegreesCommand.h"
#include "LifterV2Command.h"
#include "LoadBallFromBeltIntoThrowerCommandGroup.h"
#include "ThrowerV2Command.h"
#include "LiftDownUntilTiltCommand.h"
#include "FlapV2Command.h"

#define WAIT_SECS_FOR_ARM_RETURN 1
#define WAIT_SECS_FOR_BALL_SETTLE (0.7)
#define THROWER_POWER .1
#define WAIT_BALL_EXIT_SECS (0.2)
#define DRIVE_BACK_SPEED (0.75)
#define DRIVE_BACK_TIME 2
#define TURN_DEGREES 160 //or -180
#define DRIVE_FORWARD_TIME 2
#define DRIVE_FORWARD_SPEED (-0.75)
#define DRIVE_BACK_FROM_RAMP_TIME (0.5)
#define DRIVE_BACK_FROM_RAMP_SPEED (0.75)
#define FINAL_WAIT_TIME 2
#define FINAL_BACK_TIME 2

/**
 * This command group implements autonomous handling with shooting first and then
 * proceeding to a ramp to dump balls.  This has configurable initial delay and turning
 * angle to allow for different game strategies.
 */
AutoBasketsRampCommandGroup::AutoBasketsRampCommandGroup(float initialDelay, float desiredAngleToTurn) : CommandGroup("AutoBasketsRampCommandGroup"){
	AddSequential(new PrintCommand("Starting AutoBasketsRampCommandGroup"));
	AddSequential(new WaitCommand(initialDelay));
	
	AddSequential(new PrintCommand("Throwing"));
	AddSequential(new ThrowerV2Command(THROWER_POWER));
	// We used to wait for the thrower to retract here but that is now part of the thrower.
	
	AddSequential(new PrintCommand("Loading ball into thrower from belt"));
	AddSequential(new LoadBallFromBeltIntoThrowerCommandGroup());
	AddSequential(new WaitCommand(WAIT_SECS_FOR_BALL_SETTLE));
	AddSequential(new PrintCommand("Throwing"));
	AddSequential(new ThrowerV2Command(THROWER_POWER));
	AddSequential(new WaitCommand(WAIT_BALL_EXIT_SECS));

	AddSequential(new PrintCommand("Backing up"));
	AddSequential(new DriveStraightCommand(DRIVE_BACK_TIME, DRIVE_BACK_SPEED));
	
	AddSequential(new PrintCommand("Turning"));
	AddSequential(new TurnSpecifiedDegreesCommand(desiredAngleToTurn));
	
	AddSequential(new PrintCommand("Driving forward"));
	AddSequential(new DriveStraightCommand(DRIVE_FORWARD_TIME, DRIVE_FORWARD_SPEED));
	
	AddSequential(new PrintCommand("Backing up from ramp"));
	AddSequential(new DriveStraightCommand(DRIVE_BACK_FROM_RAMP_TIME, DRIVE_BACK_FROM_RAMP_SPEED));
	
	AddSequential(new PrintCommand("Lowering lifter"));
	AddSequential(new LiftDownUntilTiltCommand());
	
	AddSequential(new PrintCommand("Final waiting"));
	AddSequential(new WaitCommand(FINAL_WAIT_TIME));
		
	AddSequential(new PrintCommand("Final back away from ramp"));
	AddSequential(new DriveStraightCommand(FINAL_BACK_TIME, DRIVE_BACK_SPEED));
	
	AddSequential(new PrintCommand("Moving lifter up"));
	AddSequential(new LifterV2Command(UP));
	AddSequential(new PrintCommand("Completing AutoBasketsRampCommandGroup"));	
}
