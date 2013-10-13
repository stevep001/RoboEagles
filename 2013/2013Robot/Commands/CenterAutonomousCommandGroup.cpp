#include "CenterAutonomousCommandGroup.h"
#include "SetShooterTiltCommand.h"
#include "ShootFrisbeeAndIndexCommand.h"
#include "ShootOnceAndIndexCommand.h"
#include "DriveForwardCommand.h"

#define TIME_TO_WAIT_UNTILL_SHOOT 3
#define TILT_ANGLE_FOR_AUTO 26
#define TIME_INBETWEEN_SHOOT .04

CenterAutonomousCommandGroup::CenterAutonomousCommandGroup() {
	printf("CenterAutonomousCommandGroup: initializing\n");
	// Wait for things to initialize
	AddSequential(new WaitCommand(1));
	printf("Adding shooter tilt command at 30\n");
	// was 26, autonomous was high
	AddSequential(new SetShooterTiltCommand(28));
		
	//printf("Driving Back 45 inches");
	//AddSequential(new DriveForwardCommand(75));
	
	printf("Adding wait command\n");
	AddSequential(new WaitCommand(TIME_TO_WAIT_UNTILL_SHOOT));
	
	printf("Adding shoot command\n");
	AddSequential(new ShootFrisbeeAndIndexCommand());
	
	
	//printf("Moving tilt to 0\n");
	//AddSequential(new SetShooterTiltCommand(0));
	printf("CenterAutonomousCommandGroup: initialized\n");
}
