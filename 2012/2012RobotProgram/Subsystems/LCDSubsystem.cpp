#include "LCDSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/LCDUpdateCommand.h"

/**
 * This subsystem controls the driver station LCD.
 */
LCDSubsystem::LCDSubsystem() :
	Subsystem("LCDSubsystem") {
	this->lcd = DriverStationLCD::GetInstance();
}

void LCDSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new LCDUpdateCommand());
}

void LCDSubsystem::UpdateAutonomousProgram(int autonomousProgram) {
	this->autonomousProgram = autonomousProgram;
	this->updateDisplay = true;
}

void LCDSubsystem::UpdateThrowingPower(int throwingPower) {
	this->throwingPower = throwingPower;
	this->updateDisplay = true;
}

/**
 * This method is called repeatedly by the command, so that the LCD can
 * be updated to current values.
 */
void LCDSubsystem::Update() {
	
	// We only update when updateDisplay is true, so that we don't waste a bunch
	// of network bandwidth constantly updating the LCD when nothing has changed.
	
	if (this->updateDisplay) {
		UpdateLine1();
		UpdateLine2();
		UpdateLine3();
		UpdateLine4();
		lcd->UpdateLCD();

		this->updateDisplay = false;
	}
}

void LCDSubsystem::UpdateLine1() {
	lcd->PrintfLine((DriverStationLCD::Line) 1, "Throwing power: %d", this->throwingPower);
}

void LCDSubsystem::UpdateLine2() {
}

void LCDSubsystem::UpdateLine3() {
	char *modeName;
	switch (this->autonomousProgram) {
	//ABRT Cases
	case ABRT_IMMEDIATE_MODE:
		modeName = "Rt TH2 team";
		break;
	case ABRT_2SEC_MODE:
		modeName = "Rt W2 TH2 team";
		break;
	case ABRT_4SEC_MODE:
		modeName = "Rt W4 TH2 team";
		break;
	case ABRT_6SEC_MODE:
		modeName = "Rt W6 TH2 team";
		break;
	case ABRT_8SEC_MODE:
		modeName = "Rt W8 TH2 team";
		break;

		//ABRM Cases
	case ABRM_IMMEDIATE_MODE:
		modeName = "Rt TH2 middle";
		break;
	case ABRM_2SEC_MODE:
		modeName = "Rt W2 TH2 middle";
		break;
	case ABRM_4SEC_MODE:
		modeName = "Rt W4 TH2 middle";
		break;
	case ABRM_6SEC_MODE:
		modeName = "Rt W6 TH2 middle";
		break;
	case ABRM_8SEC_MODE:
		modeName = "Rt W8 TH2 middle";
		break;

		//ABLM Cases
	case ABLM_IMMEDIATE_MODE:
		modeName = "Lt TH2 middle";
		break;
	case ABLM_2SEC_MODE:
		modeName = "Lt W2 TH2 middle";
		break;
	case ABLM_4SEC_MODE:
		modeName = "Lt W4 TH2 middle";
		break;
	case ABLM_6SEC_MODE:
		modeName = "Lt W6 TH2 middle";
		break;
	case ABLM_8SEC_MODE:
		modeName = "Lt W8 TH2 middle";
		break;
		
		
		//ANGLE TESTING  MODES
	case ABRT_160_TEST:
		modeName = "RT TEAM TST R160";
		break;
	case ABRT_170_TEST:
		modeName = "RT TEAM TST R170";
		break;
	case ABRT_180_TEST:
		modeName = "RT TEAM TST R180";
		break;
	case ABRT_190_TEST:
		modeName = "RT TEAM TST R190";
		break;
	case ABRM_200_TEST:
		modeName = "RT MID TST R200";
		break;
	case ABRM_210_TEST:
		modeName = "RT MID TST R210";
		break;
	case ABRM_220_TEST:
		modeName = "RT MID TST R220";
		break;
	case ABRM_230_TEST:
		modeName = "RT MID TST R230";
		break;
		
	case BALL_EJECT_MODE:
		modeName = "Ball eject, back, drive to ramp";
		break;
		
	case AUTO_RAMP_BASKETS_MODE:
		modeName = "Throw, do nothing";
		break;
	case AUTO_DO_NOTHING_MODE:
		modeName = "Do nothing";
		break;
	default:
		modeName = "Unknown";
		break;
	}

	lcd->PrintfLine((DriverStationLCD::Line) 3, "%d %s", this->autonomousProgram, modeName);

}

void LCDSubsystem::UpdateLine4() {

}

// Put methods for controlling this subsystem
// here. Call these from Commands.

