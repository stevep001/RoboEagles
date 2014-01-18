#include "ThrowerCloseCommand.h"

ThrowerCloseCommand::ThrowerCloseCommand() {
	Requires(throwerSubsystem);
}

void ThrowerCloseCommand::Initialize() {
	throwerSubsystem->Close();
}

void ThrowerCloseCommand::Execute() {
	
}

bool ThrowerCloseCommand::IsFinished() {
	return false;
}

void ThrowerCloseCommand::End() {
	this->throwerSubsystem->Stop();
}

void ThrowerCloseCommand::Interrupted() {
	this->throwerSubsystem->Stop();
}
