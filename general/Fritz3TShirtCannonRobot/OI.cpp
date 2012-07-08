#include "OI.h"
#include "Commands/DriveWithJoystick.h"
#include "Robotmap.h"
#include "Commands/FireCannonCommand.h"
#include "Commands/FillCannonCommand.h"
#include "Commands/AimUpCommand.h"
#include "Commands/AimDownCommand.h"


OI::OI() {
	joystick = new Joystick(JOYSTICK_PORT);
	
	fireButton = new JoystickButton(joystick, FIRE_BUTTON);
	fireButton->WhileHeld(new FireCannonCommand());
	fillButton = new JoystickButton(joystick, FILL_BUTTON);
	fillButton->WhileHeld(new FillCannonCommand());
	
	aimUpButton = new JoystickButton(joystick, UP_BUTTON);
	aimUpButton->WhileHeld(new AimUpCommand());
	
	aimDownButton = new JoystickButton(joystick, DOWN_BUTTON);
	aimDownButton->WhileHeld(new AimDownCommand());
}

Joystick *OI::getJoystick() {
	return joystick;
}
