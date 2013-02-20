#include "LedControlCommand.h"

// Higher values will cause LEDs to flash
#define DISPLAY_LED_DUTY_DIVISOR	(1)


LedControlCommand::LedControlCommand() {
	Requires(ledSubsystem);
	// This is the count of iterations for duty cycle calculation
}

// Called just before this Command runs the first time
void LedControlCommand::Initialize() {
	this->count = 0;	
}

// Called repeatedly when this Command is scheduled to run
void LedControlCommand::Execute() {
	ledSubsystem->Run();
	if (this->count % DISPLAY_LED_DUTY_DIVISOR == 0)
	{
		ledSubsystem->SetPizzaBoxActive(true);
		ledSubsystem->SetShooterActive(true);
	}
	else
	{
		ledSubsystem->SetPizzaBoxActive(false);
		ledSubsystem->SetShooterActive(false);
	}
	this->count++;
}

// Make this return true when this Command no longer needs to run execute()
bool LedControlCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void LedControlCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LedControlCommand::Interrupted() {
}
