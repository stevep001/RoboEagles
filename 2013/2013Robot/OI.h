#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	Joystick *driverJoystick;
	Joystick *testJoystick;
	Joystick *testJoystick2;
	
	Button *pbTopButton;
	Button *pbBottomButton;
	Button *runShooterMotorButton;
	Button *testVisionButton;
	Button *testKickerButton;
	Button *tiltUpCommandedButton;
	Button *tiltDownCommandedButton;
	Button *shooterTilt45Button;
	
	Button *frisbeeArrivalButton;
	
	
public:
	OI();
	Joystick *GetDriverJoystick();
	Joystick *GetTestJoystick();
	Joystick *GetTestJoystick2();
};

#endif
