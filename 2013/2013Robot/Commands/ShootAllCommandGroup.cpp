#include "ShootAllCommandGroup.h"
#include "ShootFrisbeeAndIndexCommand.h"
#include "SetShooterTiltCommand.h"

ShootAllCommandGroup::ShootAllCommandGroup() {
	AddSequential(new ShootFrisbeeAndIndexCommand());
	AddSequential(new SetShooterTiltCommand(0));
}
