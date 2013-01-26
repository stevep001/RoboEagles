#include "OI.h"
#include "Robotmap.h"

OI::OI() {
	camJoystick = new Joystick(JOYSTICK);

	// Process operator interface input here.
}

Joystick *OI::GetJoystick() {
	return camJoystick;
}
