#include "OI.h"

// OI stands for Operator Interface.  This is where you create all of the devices that
// can control the robot.
OI::OI() {
	// Process operator interface input here.
	leftJoystick = new Joystick(LEFT_JOYSTICK_PORT);
	rightJoystick = new Joystick(RIGHT_JOYSTICK_PORT);
	leftKinectStick = new KinectStick(1);
	rightKinectStick = new KinectStick(2);
}

Joystick * OI::getLeftJoystick() {
	return leftJoystick;
}

Joystick * OI::getRightJoystick() {
	return rightJoystick;
}

KinectStick *OI::getLeftKinectStick() {
	return leftKinectStick;
}

KinectStick *OI::getRightKinectStick() {
	return rightKinectStick;
}
