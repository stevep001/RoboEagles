#include "OI.h"
#include "Robotmap.h"
#include "Commands/MovePBTopCommand.h"
#include "Commands/MovePBBottomCommand.h"

OI::OI() {
	// Process operator interface input here.
	this->driverJoystick = new Joystick(DRIVE_JOYSTICK_PORT);
	this->testJoystick = new Joystick(TEST_JOYSTICK_PORT);
	
	JoystickButton *pbTopButton = new JoystickButton(this->testJoystick, PB_TOP_BUTTON);
	pbTopButton->WhenPressed(new MovePBTopCommand());

	JoystickButton *pbBottomButton = new JoystickButton(this->testJoystick, PB_BOTTOM_BUTTON);
	pbBottomButton->WhenPressed(new MovePBBottomCommand());
}

Joystick *OI::GetDriverJoystick() {
	return this->driverJoystick;
}

Joystick *OI::GetTestJoystick() {
	return this->testJoystick;
}
