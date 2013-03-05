#include "LcdDisplaySubsystem.h"
#include "../Robotmap.h"
#include "../Commands/LcdDisplayCommand.h"

LcdDisplaySubsystem::LcdDisplaySubsystem() : Subsystem("LcdDisplaySubsystem") {
	
}
    
void LcdDisplaySubsystem::InitDefaultCommand() {
	SetDefaultCommand(new LcdDisplayCommand());
	this->line1Updated = false;
}

void LcdDisplaySubsystem::SetTiltAngle(float tiltAngle)
{
	this->tiltAngle = tiltAngle;
	this->line1Updated = true;
}

void LcdDisplaySubsystem::UpdateLines()
{
	DriverStationLCD *lcd = DriverStationLCD::GetInstance();
	
	lcd->PrintfLine(DriverStationLCD::kUser_Line1, "Tilt angle: %f", this->tiltAngle);
	lcd->UpdateLCD();
}
