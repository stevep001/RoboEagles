#include "OI.h"
#include "Robotmap.h"
#include "Commands/MovePBTopCommand.h"
#include "Commands/MovePBBottomCommand.h"
#include "Commands/ManualTiltUpCommand.h"
#include "Commands/ManualTiltDownCommand.h"
#include "Commands/RunShooterAtPowerCommand.h"
#include "Commands/TestVisionCommand.h"
#include "Commands/TestKickerCommand.h"
#include "Commands/TestTiltCommand.h"

OI::OI() {
	this->driverJoystick = new Joystick(DRIVE_JOYSTICK_PORT);
	this->testJoystick = new Joystick(TEST_JOYSTICK_PORT);
	
	this->pbTopButton = new JoystickButton(this->testJoystick, PB_TOP_BUTTON);
	this->pbTopButton->WhenPressed(new MovePBTopCommand());

	this->pbBottomButton = new JoystickButton(this->testJoystick, PB_BOTTOM_BUTTON);
	this->pbBottomButton->WhenPressed(new MovePBBottomCommand());
	
	this->tiltUpButton = new JoystickButton(this->testJoystick, TILT_UP_MANUAL_BUTTON);
	this->tiltUpButton->WhileHeld(new TestTiltCommand(-.8));
	
	this->tiltDownButton = new JoystickButton(this->testJoystick, TILT_DOWN_MANUAL_BUTTON);
	this->tiltDownButton->WhileHeld(new TestTiltCommand(.4));
	
	this->runShooterMotorButton = new JoystickButton(this->testJoystick, RUN_SHOOTER_BUTTON);
	this->runShooterMotorButton->WhileHeld(new RunShooterAtPowerCommand(.8));
	
	this->testKickerButton = new JoystickButton(this->testJoystick, TEST_KICKER_BUTTON);
	this->testKickerButton->WhenPressed(new TestKickerCommand());
	
	this->testVisionButton = new JoystickButton(this->testJoystick, TEST_VISION_BUTTON);
	this->testVisionButton->WhenPressed(new TestVisionCommand());
}

Joystick *OI::GetDriverJoystick() {
	return this->driverJoystick;
}

Joystick *OI::GetTestJoystick() {
	return this->testJoystick;
}
