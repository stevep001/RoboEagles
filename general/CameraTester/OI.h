#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	Joystick *camJoystick;

public:
	OI();
	Joystick *GetJoystick();
};

#endif
