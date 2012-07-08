#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:

	Joystick *joystick;
	JoystickButton *fireButton;
	JoystickButton *fillButton;
	JoystickButton *aimUpButton;
	JoystickButton *aimDownButton;

public:
	OI();
	Joystick *getJoystick();
};

#endif
