#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	Joystick *driverJoystick;
	Joystick *testJoystick;
	
	JoystickButton *pbTopButton;
	JoystickButton *pbBottomButton;
	JoystickButton *tiltUpButton;
	JoystickButton *tiltDownButton;
	JoystickButton *runShooterMotorButton;
	JoystickButton *testVisionButton;
	JoystickButton *testKickerButton;
public:
	OI();
	Joystick *GetDriverJoystick();
	Joystick *GetTestJoystick();
};

#endif
