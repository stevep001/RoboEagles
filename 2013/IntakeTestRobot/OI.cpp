#include "OI.h"
#include "Robotmap.h"
#include "Commands/RunIntakeCommand.h"
#include "Commands/AtLoadingStationCommand.h"
#include "Commands/StowPanCommand.h"
#include "Commands/DeployPanCommand.h"

OI::OI() {
	// Process operator interface input here.
	this->driverJoystick = new Joystick(DRIVER_JOYSTICK);
	this->testJoystick2 = new Joystick(LOADER_TEST_JOYSTICK);
	
//	this->runIntakeButton = new JoystickButton(this->testJoystick2, 1);
//	this->runIntakeButton->WhileHeld(new RunIntakeCommand());
//	
	
	this->atLoadingStationButton = new JoystickButton(this->testJoystick2, 6);
	this->atLoadingStationButton->WhileHeld(new AtLoadingStationCommand());

	this->stowPanButton = new JoystickButton(this->testJoystick2, 7);
	this->stowPanButton->WhenPressed(new StowPanCommand());
	
	this->deployPanButton = new JoystickButton(this->testJoystick2, 8);
	this->deployPanButton->WhenPressed(new DeployPanCommand());
	
}

Joystick* OI::GetDriverJoystick()
{
	return this->driverJoystick;
}
