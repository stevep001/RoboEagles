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
#include "Commands/MoveToNextFiringPositionCommand.h"
#include "Commands/MoveToNextLoadingPositionCommand.h"
#include "Commands/AtLoadingStationCommand.h"
#include "Commands/StowPanCommand.h"
#include "Commands/DeployPanCommand.h"
#include "Commands/CenterAutonomousCommandGroup.h"
#include "Commands/LeftPyramidAutonomousCommandGroup.h"
#include "Commands/SetTestShootingPowerCommand.h"
#include "Commands/ShootAllCommandGroup.h"
#include "Commands/ShootOnceAndIndexCommand.h"
#include "Commands/TurnSpecifiedDegreesPIDCommand.h"
#include "FrisbeeArrivalButton.h"

OI::OI() {
	this->driverJoystick = new Joystick(DRIVE_JOYSTICK_PORT);
	this->shooterJoystick = new Joystick(SHOOTER_JOYSTICK_PORT);
	
	// Automation buttons
	
	this->frisbeeArrivalButton = new FrisbeeArrivalButton();
	this->frisbeeArrivalButton->WhenPressed(new OnFrisbeeArrivalCommand());
	
	// Driver joystick buttons
	
	this->atLoadingStationButton = new JoystickButton(this->driverJoystick, PAN_FEEDER_STATION_BUTTON);
	this->atLoadingStationButton->WhileHeld(new AtLoadingStationCommand());

	this->stowPanButton = new JoystickButton(this->driverJoystick, STOW_PAN_BUTTON);
	this->stowPanButton->WhenPressed(new StowPanCommand());
	
	this->deployPanButton = new JoystickButton(this->driverJoystick, DEPLOY_PAN_BUTTON);
	this->deployPanButton->WhenPressed(new DeployPanCommand());		
	
	// Shooter joystick buttons
	//this->tiltTo26DegreeButton = JoystickButton(this->shooterJoystick, 9);
	//this->tiltTo26DegreeButton->WhenPressed(new SetShooterTiltCommand(26));
	
	this->shootAllFrisbeesCommand = new JoystickButton(this->shooterJoystick, SHOOT_FRISBEE_INDEX_BUTTON);
	this->shootAllFrisbeesCommand->WhenPressed(new ShootAllCommandGroup());
	
	this->shootOnceAndIndexButton = new JoystickButton(this->shooterJoystick, SHOOT_ONE_FRISBEE_AND_INDEX_BUTTON);
	this->shootOnceAndIndexButton->WhenPressed(new ShootOnceAndIndexCommand);
	
	this->tiltUpCommandedButton = new JoystickButton(this->shooterJoystick, TILT_UP_COMMANDED_BUTTON);
	this->tiltUpCommandedButton->WhenPressed(new ManualTiltUpCommand());

	this->tiltDownCommandedButton = new JoystickButton(this->shooterJoystick, TILT_DOWN_COMMANDED_BUTTON);
	this->tiltDownCommandedButton->WhenPressed(new ManualTiltDownCommand());
	
	this->pizzaBoxUpButton = new JoystickButton(this->shooterJoystick, PIZZA_BOX_UP_BUTTON);
	this->pizzaBoxUpButton->WhenPressed(new MovePBTopCommand());
	
	this->pizzaBoxDownButton = new JoystickButton(this->shooterJoystick, PIZZA_BOX_DOWN_BUTTON);
	this->pizzaBoxDownButton->WhenPressed(new MovePBBottomCommand());
	
	this->tiltToZeroButton = new JoystickButton(this->shooterJoystick, TILT_TO_ZERO_BUTTON);
	this->tiltToZeroButton->WhenPressed(new SetShooterTiltCommand(0));
	
	// Test joystick 1
	this->testJoystick = new Joystick(TEST_JOYSTICK_PORT);
	
	this->pbTopButton = new JoystickButton(this->testJoystick, PB_TOP_BUTTON);
	this->pbTopButton->WhenPressed(new MovePBTopCommand());

	this->pbBottomButton = new JoystickButton(this->testJoystick, PB_BOTTOM_BUTTON);
	this->pbBottomButton->WhenPressed(new MovePBBottomCommand());

//	this->runShooterMotorButton = new JoystickButton(this->testJoystick, RUN_SHOOTER_BUTTON);
//	this->runShooterMotorButton->WhileHeld(new RunShooterAtPowerCommand(.8));
	
	this->testKickerButton = new JoystickButton(this->testJoystick, TEST_KICKER_BUTTON);
	this->testKickerButton->WhenPressed(new TestKickerCommand());
	
	this->testVisionButton = new JoystickButton(this->testJoystick, TEST_VISION_BUTTON);
	this->testVisionButton->WhenPressed(new TestVisionCommand());
	
	this->shooterTilt45Button = new JoystickButton(this->testJoystick, SHOOTER_TILT_45_BUTTON);
	this->shooterTilt45Button->WhenPressed(new SetShooterTiltCommand(45));
	
	//Test Joystick 2
	this->testJoystick2 = new Joystick(TEST_JOYSTICK_PORT_TWO);
	
	this->testPidTurnNeg45Button = new JoystickButton(this->testJoystick2, TEST_TURN_NEG_45);
	this->testPidTurnNeg45Button->WhenPressed(new TurnSpecifiedDegreesPIDCommand(-45));
	
	this->testPidTurnNeg90Button = new JoystickButton(this->testJoystick2, TEST_TURN_NEG_90);
	this->testPidTurnNeg90Button->WhenPressed(new TurnSpecifiedDegreesPIDCommand(-90));
	
	this->testPidTurnPos45Button = new JoystickButton(this->testJoystick2, TEST_TURN_POS_45);
	this->testPidTurnPos45Button->WhenPressed(new TurnSpecifiedDegreesPIDCommand(45));
	
	this->testPidTurnPos90Button = new JoystickButton(this->testJoystick2, TEST_TURN_POS_90);
	this->testPidTurnPos90Button->WhenPressed(new TurnSpecifiedDegreesPIDCommand(90));
	
	// Buttons for smart dashboard
	SmartDashboard::PutData("Move next firing position", new MoveToNextFiringPositionCommand());
	SmartDashboard::PutData("Move next loading position", new MoveToNextLoadingPositionCommand());
	SmartDashboard::PutData("Move PB Top", new MovePBTopCommand());
	SmartDashboard::PutData("Move PB Bottom", new MovePBBottomCommand());
	SmartDashboard::PutData("Center Autonomous", new CenterAutonomousCommandGroup());
	SmartDashboard::PutData("Left Autonomous", new LeftPyramidAutonomousCommandGroup());
			
	SmartDashboard::PutData("Set test shooter power", new SetTestShootingPowerCommand());
}

Joystick *OI::GetDriverJoystick() {
	return this->driverJoystick;
}

Joystick *OI::GetTestJoystick() {
	return this->testJoystick;
}
