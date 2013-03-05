#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	Joystick *testJoystick2;
	Joystick *driverJoystick;
	
	JoystickButton *runIntakeButton;
	JoystickButton *atLoadingStationButton;
	JoystickButton *stowPanButton;
	JoystickButton *deployPanButton;
public:
	OI();
	Joystick* GetDriverJoystick();
};

#endif
