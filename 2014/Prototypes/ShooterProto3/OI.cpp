#include "OI.h"
#include "Commands/ThrowerCloseCommand.h"
#include "Commands/ThrowerOpenCommand.h"

OI::OI() {
	// Process operator interface input here.
	this->stick = new Joystick(1);
	
	this->throwerCloseButton = new JoystickButton(stick, 1);
	this->throwerCloseButton->WhileHeld(new ThrowerCloseCommand());
	
	this->throwerOpenButon = new JoystickButton(stick, 4);
	this->throwerOpenButon->WhileHeld(new ThrowerOpenCommand());
}
