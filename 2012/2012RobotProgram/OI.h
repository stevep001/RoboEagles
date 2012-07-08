#ifndef OI_H
#define OI_H

#include "WPILib.h"


#define THROWING_POWER_INCREMENT 2

class OI {
	
private:
	SmartDashboard *smartDashboard;

	// Joysticks
	
	//	Joystick *leftJoystick;
	Joystick *rightJoystick;
	Joystick *throwJoystick;
	//Joystick *liftJoystick;
	KinectStick *kinectStick;
	
	// Auto Turn
	JoystickButton *turnLeftButton;
	JoystickButton *turnRightButton;
	JoystickButton *rampDriveButton;
	
	// Run Autonomous program
	JoystickButton *autonomousButton;
	
	JoystickButton *stopAutonomousDrive;
	
	// Traffic cop
//	JoystickButton *copOffButton;
//	JoystickButton *copUpButton;
//	JoystickButton *copDownButton;
//	JoystickButton *copStopButton;
	
	JoystickButton *autonomousModeSelectButton;
	JoystickButton *driveForwardToFloorTransitionButton;
	
	// Thrower
	JoystickButton *throwingPowerIncreaseButton;
	JoystickButton *throwingPowerDecreaseButton;
	JoystickButton *throwButton;
	JoystickButton *flapToggleButton;
	JoystickButton *stopBallLoadingButton;

public:
	OI();
	SmartDashboard *getSmartDashboard();
	Joystick *getRightJoystick();
	Joystick *getThrowJoystick();
	Joystick *getLiftJoystick();
	KinectStick *getKinectStick();
};

#endif
