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
	Button *tiltToZeroButton;
	//Button *tiltAngle;
	Button *tiltTo26DegreeButton;
	
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
	
	//Test Joystick 2
	Button *testPidTurnPos45Button;
	Button *testPidTurnNeg45Button;
	Button *testPidTurnPos90Button;
	Button *testPidTurnNeg90Button;

	
	
public:
	OI();
	Joystick *GetDriverJoystick();
	Joystick *GetTestJoystick();
	Joystick *GetTestJoystick2();
};

#endif
