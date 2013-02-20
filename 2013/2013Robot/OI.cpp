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
#include "Commands/ShootFrisbeeAndIndexCommand.h"
#include "Commands/LiftPanCommand.h"
#include "Commands/MoveToNextFiringPositionCommand.h"
#include "Commands/MoveToNextLoadingPositionCommand.h"
#include "FrisbeeArrivalButton.h"

OI::OI() {
	this->driverJoystick = new Joystick(DRIVE_JOYSTICK_PORT);
	
	// Automation buttons
	
	this->frisbeeArrivalButton = new FrisbeeArrivalButton();
	this->frisbeeArrivalButton->WhenPressed(new OnFrisbeeArrivalCommand());
	
	// Driver joystick buttons
	
	this->liftPanButton = new JoystickButton(this->driverJoystick, LIFT_PAN_BUTTON);
	this->liftPanButton->WhenPressed(new LiftPanCommand(true));
	
	this->lowerPanButton = new JoystickButton(this->driverJoystick, LOWER_PAN_BUTTON);
	this->lowerPanButton->WhenPressed(new LiftPanCommand(false));
			
	// Test joystick 1
	this->testJoystick = new Joystick(TEST_JOYSTICK_PORT);
	
	this->shootFrisbeeIndexButton = new JoystickButton(this->testJoystick, SHOOT_FRISBEE_INDEX_COMMAND);
	this->shootFrisbeeIndexButton->WhenPressed(new ShootFrisbeeAndIndexCommand());
	
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
	
	// Buttons for smart dashboard
	SmartDashboard::PutData("Move next firing position", new MoveToNextFiringPositionCommand());
	SmartDashboard::PutData("Move next loading position", new MoveToNextLoadingPositionCommand());
	SmartDashboard::PutData("Move PB Top", new MovePBTopCommand());
	SmartDashboard::PutData("Move PB Bottom", new MovePBBottomCommand());
			
}

Joystick *OI::GetDriverJoystick() {
	return this->driverJoystick;
}

Joystick *OI::GetTestJoystick() {
	return this->testJoystick;
}
