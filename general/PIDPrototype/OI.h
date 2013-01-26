#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	JoystickButton *positionHoldButton;
	JoystickButton *rpmHoldButton;
	JoystickButton *showEncoderButton;
	Joystick *joystick;
	Preferences *preferences;
public:
	OI();
	SmartDashboard *getSmartDashboard();
	void DisplayPIDController(PIDController *controller);
	void DisplayEncoder(Encoder *encoder);

};

#endif
