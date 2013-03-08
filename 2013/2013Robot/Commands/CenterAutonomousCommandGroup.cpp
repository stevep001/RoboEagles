#include "CenterAutonomousCommandGroup.h"
#include "SetShooterTiltCommand.h"
#include "ShootFrisbeeAndIndexCommand.h"


CenterAutonomousCommandGroup::CenterAutonomousCommandGroup() {
	printf("CenterAutonomousCommandGroup: initializing\n");
	printf("Adding shooter tilt command\n");
	AddSequential(new SetShooterTiltCommand(15));
	printf("Adding wait command\n");
	AddSequential(new WaitCommand(2));
	printf("Adding shoot command\n");
	AddSequential(new ShootFrisbeeAndIndexCommand());
	printf("CenterAutonomousCommandGroup: initialized\n");
}
