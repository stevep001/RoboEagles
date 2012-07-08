#include "SelectAutonomousProgramCommand.h"

SelectAutonomousProgramCommand::SelectAutonomousProgramCommand() {
	lcdSubsystem->UpdateAutonomousProgram(this->autonomousProgram);
}

void SelectAutonomousProgramCommand::Initialize() {
}

void SelectAutonomousProgramCommand::Execute() {
	this->autonomousProgram++;
	if (this->autonomousProgram > MAX_AUTONOMOUS_MODE)
	{
		this->autonomousProgram = MIN_AUTONOMOUS_MODE;
	}
	
	lcdSubsystem->UpdateAutonomousProgram(this->autonomousProgram);
}

bool SelectAutonomousProgramCommand::IsFinished() {
	return true;
}

void SelectAutonomousProgramCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SelectAutonomousProgramCommand::Interrupted() {
}
