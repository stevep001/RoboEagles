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
#include "Commands/SetShooterTiltCommand.h"
#include "Commands/OnFrisbeeArrivalCommand.h"
#include "FrisbeeArrivalButton.h"

OI::OI() {
	this->driverJoystick = new Joystick(DRIVE_JOYSTICK_PORT);
	
	// Automation buttons
	
	this->frisbeeArrivalButton = new FrisbeeArrivalButton();
	this->frisbeeArrivalButton->WhenPressed(new OnFrisbeeArrivalCommand());
	
	// Test joystick 1
	this->testJoystick = new Joystick(TEST_JOYSTICK_PORT);
	
	this->pbTopButton = new JoystickButton(this->testJoystick, PB_TOP_BUTTON);
	this->pbTopButton->WhenPressed(new MovePBTopCommand());

	this->pbBottomButton = new JoystickButton(this->testJoystick, PB_BOTTOM_BUTTON);
	this->pbBottomButton->WhenPressed(new MovePBBottomCommand());

	this->runShooterMotorButton = new JoystickButton(this->testJoystick, RUN_SHOOTER_BUTTON);
	this->runShooterMotorButton->WhileHeld(new RunShooterAtPowerCommand(.8));
	
	this->testKickerButton = new JoystickButton(this->testJoystick, TEST_KICKER_BUTTON);
	this->testKickerButton->WhenPressed(new TestKickerCommand());
	
	this->testVisionButton = new JoystickButton(this->testJoystick, TEST_VISION_BUTTON);
	this->testVisionButton->WhenPressed(new TestVisionCommand());
	
	this->tiltUpCommandedButton = new JoystickButton(this->testJoystick, TILT_UP_COMMANDED_BUTTON);
	this->tiltUpCommandedButton->WhenPressed(new ManualTiltUpCommand());

	this->tiltDownCommandedButton = new JoystickButton(this->testJoystick, TILT_DOWN_COMMANDED_BUTTON);
	this->tiltDownCommandedButton->WhenPressed(new ManualTiltDownCommand());
	
	this->shooterTilt45Button = new JoystickButton(this->testJoystick, SHOOTER_TILT_45_BUTTON);
	this->shooterTilt45Button->WhenPressed(new SetShooterTiltCommand(45));
			
}

Joystick *OI::GetDriverJoystick() {
	return this->driverJoystick;
}

Joystick *OI::GetTestJoystick() {
	return this->testJoystick;
}
