#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	static const int LEFT_JOYSTICK_PORT = 1; 
	static const int RIGHT_JOYSTICK_PORT = 2; 
	
	Joystick *leftJoystick;
	Joystick *rightJoystick;
	KinectStick *leftKinectStick;
	KinectStick *rightKinectStick;

public:
	OI();
	Joystick *getLeftJoystick();
	Joystick *getRightJoystick();
	KinectStick *getLeftKinectStick();	
	KinectStick *getRightKinectStick();
};

#endif
