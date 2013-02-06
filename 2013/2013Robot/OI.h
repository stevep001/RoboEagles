#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	Joystick *driverJoystick;
	Joystick *testJoystick;
public:
	OI();
	Joystick *GetDriverJoystick();
	Joystick *GetTestJoystick();
};

#endif
