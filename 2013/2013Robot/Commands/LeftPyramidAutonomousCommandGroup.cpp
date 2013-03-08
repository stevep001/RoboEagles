#include "LeftPyramidAutonomousCommandGroup.h"
#include "SetShooterTiltCommand.h"
#include "TurnSpecifiedDegreesCommand.h"
#include "DriveForwardCommand.h"
#include "ShootFrisbeeAndIndexCommand.h"

LeftPyramidAutonomousCommandGroup::LeftPyramidAutonomousCommandGroup() {
	AddSequential(new SetShooterTiltCommand(15));
	AddSequential(new DriveForwardCommand(24));
	AddSequential(new TurnSpecifiedDegreesCommand(100));
	AddSequential(new ShootFrisbeeAndIndexCommand());
}
