#include "KillVisionTargetingCommandGroupCommand.h"

KillVisionTargetingCommandGroupCommand::KillVisionTargetingCommandGroupCommand(VisionTargetingCommandGroup *visionTargeting) {
	printf("[KillVisionTargetingCommandGroupCommand] Is Being Constructed\n");
	this->m_visionTargeting = visionTargeting;
	printf("[KillVisionTargetingCommandGroupCommand] Has Been Constructed\n");
}


void KillVisionTargetingCommandGroupCommand::Initialize() {
	printf("[KillVisionTargetingCommandGroupCommand] Killing VisionTargetingCommandGroupCommand\n");
	this->m_visionTargeting->Cancel();
}


void KillVisionTargetingCommandGroupCommand::Execute() {
	
}

bool KillVisionTargetingCommandGroupCommand::IsFinished() {
	return true;
}

void KillVisionTargetingCommandGroupCommand::End() {
	
}

void KillVisionTargetingCommandGroupCommand::Interrupted() {
}
