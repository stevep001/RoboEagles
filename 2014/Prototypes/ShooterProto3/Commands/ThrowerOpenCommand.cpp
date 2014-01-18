#include "ThrowerOpenCommand.h"

ThrowerOpenCommand::ThrowerOpenCommand() {
	Requires(throwerSubsystem);
}

void ThrowerOpenCommand::Initialize() {
	this->throwerSubsystem->Open();
	
}

void ThrowerOpenCommand::Execute() {
}

bool ThrowerOpenCommand::IsFinished() {
	return false;
}

void ThrowerOpenCommand::End() {
	this->throwerSubsystem->Stop();
}

void ThrowerOpenCommand::Interrupted() {
	this->throwerSubsystem->Stop();
}
