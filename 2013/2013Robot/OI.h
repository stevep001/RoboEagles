#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	Joystick *driverJoystick;
	Joystick *shooterJoystick;
	Joystick *testJoystick;
	Joystick *testJoystick2;

	// Driver joystick
	Button *atLoadingStationButton;
	Button *stowPanButton;
	Button *deployPanButton;
	Button *pizzaBoxUpButton;
	Button *pizzaBoxDownButton;
	
	//Shooter Joystick
	Button *shootOnceAndIndexButton;
	
	// Test joystick
	Button *pbTopButton;
	Button *pbBottomButton;
	Button *runShooterMotorButton;
	Button *testVisionButton;
	Button *testKickerButton;
	Button *tiltUpCommandedButton;
	Button *tiltDownCommandedButton;
	Button *shooterTilt45Button;
	Button *shootAllFrisbeesCommand;
	Button *frisbeeArrivalButton;
	
	

	
	
public:
	OI();
	Joystick *GetDriverJoystick();
	Joystick *GetTestJoystick();
	Joystick *GetTestJoystick2();
};

#endif
