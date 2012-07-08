#include "LoadBallFromBeltIntoThrowerCommandGroup.h"
#include "BeltCommand.h"
#include "FlapV2Command.h"
#include "WaitForBallInThrowerCommand.h"

/**
 * Command group that causes a ball to be loaded into the thrower.
 */
LoadBallFromBeltIntoThrowerCommandGroup::LoadBallFromBeltIntoThrowerCommandGroup() 
	: CommandGroup("LoadBallFromBeltIntoThrowerCommandGroup"){
	AddSequential(new BeltCommand(true));
	AddSequential(new FlapV2Command(true));
	AddSequential(new WaitForBallInThrowerCommand());
	AddSequential(new BeltCommand(false));
}
