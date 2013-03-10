#include "CenterAutonomousCommandGroup.h"
#include "SetShooterTiltCommand.h"
#include "ShootFrisbeeAndIndexCommand.h"


CenterAutonomousCommandGroup::CenterAutonomousCommandGroup() {
	printf("CenterAutonomousCommandGroup: initializing\n");
	// Wait for things to initialize
	AddSequential(new WaitCommand(1));
	printf("Adding shooter tilt command\n");
	// was 26, autonomous was high
	AddSequential(new SetShooterTiltCommand(24));
	printf("Adding wait command\n");
	AddSequential(new WaitCommand(2));
	printf("Adding shoot command\n");
	AddSequential(new ShootFrisbeeAndIndexCommand());
	printf("Moving tilt to 0\n");
	AddSequential(new SetShooterTiltCommand(0));
	printf("CenterAutonomousCommandGroup: initialized\n");
}
