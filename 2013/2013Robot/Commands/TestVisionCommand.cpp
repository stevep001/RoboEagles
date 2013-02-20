#include "TestVisionCommand.h"
#include "../Subsystems/VisionSubsystem.h"

TestVisionCommand::TestVisionCommand() {
	Requires(visionSubsystem);
}

// Called just before this Command runs the first time
void TestVisionCommand::Initialize() {
	printf("TestVisionCommand: initializing.  This actually does the procesing.\n");
	visionSubsystem->ProcessImage();
	
	this->PrintTargetValues(TOP_TARGET);
	this->PrintTargetValues(MIDDLE_TARGET);
	this->PrintTargetValues(BOTTOM_TARGET);
	
	printf("TestVisionCommand: completed\n");
}

void TestVisionCommand::PrintTargetValues(int targetId)
{
	if (visionSubsystem->IsTargetVisible(targetId))
	{
		printf("Target %d visible: azimuth %f; distance %f; pitch %f", targetId, 
			visionSubsystem->GetTargetAzimuth(targetId),
			visionSubsystem->GetTargetDistance(targetId), visionSubsystem->GetTargetPitch(targetId));
	}
}

// Called repeatedly when this Command is scheduled to run
void TestVisionCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool TestVisionCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void TestVisionCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestVisionCommand::Interrupted() {
}
