#include "OI.h"
#include "Robotmap.h"
#include "Commands/MovePBTopCommand.h"
#include "Commands/MovePBBottomCommand.h"
#include "Commands/ManualTiltUpCommand.h"
#include "Commands/ManualTiltDownCommand.h"

OI::OI() {
	// Process operator interface input here.
	this->driverJoystick = new Joystick(DRIVE_JOYSTICK_PORT);
	this->testJoystick = new Joystick(TEST_JOYSTICK_PORT);
	
	JoystickButton *pbTopButton = new JoystickButton(this->testJoystick, PB_TOP_BUTTON);
	pbTopButton->WhenPressed(new MovePBTopCommand());

	JoystickButton *pbBottomButton = new JoystickButton(this->testJoystick, PB_BOTTOM_BUTTON);
	pbBottomButton->WhenPressed(new MovePBBottomCommand());
	
	JoystickButton *tiltUpButton = new JoystickButton(this->testJoystick, TILT_UP_BUTTON);
	tiltUpButton->WhenPressed(new ManualTiltUpCommand());
	
	JoystickButton *tiltDownButton = new JoystickButton(this->testJoystick, TILT_DOWN_BUTTON);
	tiltDownButton->WhenPressed(new ManualTiltDownCommand());
}

Joystick *OI::GetDriverJoystick() {
	return this->driverJoystick;
}

Joystick *OI::GetTestJoystick() {
	return this->testJoystick;
}
