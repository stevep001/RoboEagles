#include "LEDSubsystem.h"
#include "../Commands/LedControlCommand.h"
#include "../Robotmap.h"

LEDSubsystem::LEDSubsystem() : Subsystem("LEDSubsystem") {
	this->blueStrip = new Solenoid(BLUE_LED_STRIP);
	this->yellowStrip = new Solenoid(YELLOW_LED_STRIP);
	this->greenRing = new Solenoid(GREEN_RING);
	
	this->yellowTimer = new Timer();
	this->blueTimer = new Timer();
}
    
void LEDSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new LedControlCommand());
}

void LEDSubsystem::Run() {
	this->greenRing->Set(true);
}

void LEDSubsystem::SetPizzaBoxActive(bool active)
{
	this->blueStrip->Set(active);
}

void LEDSubsystem::SetShooterActive(bool active)
{
	this->yellowStrip->Set(active);
}
