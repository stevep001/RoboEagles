#include "OI.h"
#include "Robotmap.h"
#include "Commands/TurnSpecifiedDegreesCommand.h"
#include "Commands/DriveWithJoystick.h"
#include "Commands/RampDriveCommand.h"
#include "Commands/TrafficCopStopCommand.h"
#include "Commands/TrafficCopBlankCommand.h"
#include "Commands/ArrowUpCommand.h"
#include "Commands/ArrowDownCommand.h"
#include "Commands/AutoBasketsRampCommandGroup.h"
#include "Commands/DriveStraightCommand.h"
#include "Commands/ChangeThrowingPowerCommand.h"
#include "Commands/ThrowerV2Command.h"
#include "Commands/FlapV2Command.h"
#include "Commands/SelectAutonomousProgramCommand.h"
#include "Commands/StopLoadingCommand.h"
#include "Commands/DriveForwardToFloorTransitionCommand.h"

OI::OI() {
	// Process operator interface input here.
	//leftJoystick = new Joystick(LEFT_JOYSTICK_PORT);
	rightJoystick = new Joystick(RIGHT_JOYSTICK_PORT);
	throwJoystick = new Joystick(THROW_JOYSTICK_PORT);
	//liftJoystick = new Joystick(LIFT_JOYSTICK_PORT);
	kinectStick = new KinectStick(1);
	smartDashboard = SmartDashboard::GetInstance();

	// Testing button
	
	autonomousButton = new JoystickButton(rightJoystick, RUN_AUTONOMOUS);
	autonomousButton->WhenPressed(new AutoBasketsRampCommandGroup(0, 180));
	//autonomousButton->WhenPressed(new DriveStraightCommand(5, .6));
	
	// Shut these off -- useful for testing only
//	turnLeftButton = new JoystickButton(rightJoystick, TURN_LEFT_BUTTON);
//	turnLeftButton->WhenPressed(new TurnSpecifiedDegreesCommand(-90));
//	
//	turnRightButton = new JoystickButton(rightJoystick, TURN_RIGHT_BUTTON);
//	turnRightButton->WhenPressed(new TurnSpecifiedDegreesCommand(90));
	
	// Driver joystick
	
	rampDriveButton = new JoystickButton(rightJoystick, RAMP_DRIVE_BUTTON);
	rampDriveButton->WhileHeld(new RampDriveCommand());
	
	autonomousModeSelectButton = new JoystickButton(rightJoystick, SELECT_AUTONOMOUS_BUTTON);
	autonomousModeSelectButton->WhenPressed(new SelectAutonomousProgramCommand());
	
	driveForwardToFloorTransitionButton = new JoystickButton(rightJoystick, DRIVE_FORWARD_TO_TRANSITION_BUTTON);
	driveForwardToFloorTransitionButton->WhenPressed(new DriveForwardToFloorTransitionCommand());

	stopAutonomousDrive = new JoystickButton(rightJoystick, STOP_AUTONOMOUS_DRIVE);
//	stopAutonomousDrive->WhenPressed(new DoNothingDrivingCommand());

	// Throwing joystick 
	
	throwingPowerIncreaseButton = new JoystickButton(throwJoystick, INCREASE_BUTTON);
	throwingPowerIncreaseButton->WhenPressed(new ChangeThrowingPowerCommand(THROWING_POWER_INCREMENT));
	
	throwingPowerDecreaseButton = new JoystickButton(throwJoystick, DECREASE_BUTTON);
	throwingPowerDecreaseButton->WhenPressed(new ChangeThrowingPowerCommand(-THROWING_POWER_INCREMENT));
	
	throwButton = new JoystickButton(throwJoystick, THROW_TRIGGER_BUTTON);
	throwButton->WhenPressed(new ThrowerV2Command());
	
	
	//flapToggleButton = new JoystickButton(throwJoystick, FLAP_TOGGLE_BUTTON);
	//flapToggleButton->WhenPressed(new FlapV2Command());
	
	stopBallLoadingButton = new JoystickButton(throwJoystick, STOP_BALL_LOADING_BUTTON);
	stopBallLoadingButton->WhileHeld(new StopLoadingCommand());
}

SmartDashboard *OI::getSmartDashboard() {
	return smartDashboard;
}

Joystick *OI::getRightJoystick() {
	return rightJoystick;
}

Joystick *OI::getThrowJoystick() {
	return throwJoystick;
}

Joystick *OI::getLiftJoystick(){
	return rightJoystick;
}

KinectStick *OI::getKinectStick() {
	return kinectStick;
}
