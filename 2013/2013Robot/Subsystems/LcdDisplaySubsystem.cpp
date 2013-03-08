#include "LcdDisplaySubsystem.h"
#include "../Robotmap.h"
#include "../Commands/LcdDisplayCommand.h"

LcdDisplaySubsystem::LcdDisplaySubsystem() : Subsystem("LcdDisplaySubsystem") {
	
}
    
void LcdDisplaySubsystem::InitDefaultCommand() {
	SetDefaultCommand(new LcdDisplayCommand());
}

void LcdDisplaySubsystem::SetTiltAngle(float tiltAngle)
{
}

void LcdDisplaySubsystem::UpdateLines()
{
	DriverStationLCD *lcd = DriverStationLCD::GetInstance();
	
	lcd->PrintfLine(DriverStationLCD::kUser_Line1, "Tilt angle: %f", CommandBase::shooterTiltSubsystem->GetAngle());
	lcd->UpdateLCD();
}
