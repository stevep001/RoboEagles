#include "LCDUpdateCommand.h"

/**
 * This command exists to cause the LCD to be updated on each iteration.
 * 
 * Most of the logic related to this is in the LCDSubsystem.
 */

LCDUpdateCommand::LCDUpdateCommand() {
	Requires(lcdSubsystem);
}

void LCDUpdateCommand::Initialize() {
	
}

void LCDUpdateCommand::Execute() {
	lcdSubsystem->Update();
}

bool LCDUpdateCommand::IsFinished() {
	return false;
}

void LCDUpdateCommand::End() {
	
}

void LCDUpdateCommand::Interrupted() {
}
