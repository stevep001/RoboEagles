#include "OI.h"
#include "commands/PositionHoldingCommand.h"
#include "Commands/RPMHoldingCommand.h"
#include "Commands/ShowEncoderCommand.h"

OI::OI() {
	joystick = new Joystick(1);
	positionHoldButton = new JoystickButton(joystick, 7);
	positionHoldButton->WhileHeld(new PositionHoldingCommand());
	
	rpmHoldButton = new JoystickButton(joystick, 8);
	rpmHoldButton->WhileHeld(new RPMHoldingCommand());
	
	showEncoderButton = new JoystickButton(joystick, 9);
	showEncoderButton->WhileHeld(new ShowEncoderCommand());
	
	preferences = Preferences::GetInstance();
	preferences->GetDouble("setpoint", 1);
	preferences->GetDouble("blah", 1234);
}

SmartDashboard* OI::getSmartDashboard()
{
	return SmartDashboard::GetInstance();
}

void OI::DisplayEncoder(Encoder *encoder)
{
	SmartDashboard *sd = getSmartDashboard();

	sd->PutDouble("Encoder distance", encoder -> GetDistance());
	sd->PutDouble("Encoder rate", encoder -> GetRate());
	sd->PutInt("Encoder count", encoder->Get());
	sd->PutInt("Encoder raw", encoder->GetRaw());
	sd->PutDouble("Encoder last period", encoder->GetPeriod());
	sd->PutBoolean("Encoder stopped", encoder->GetStopped());
	sd->PutBoolean("Encoder direction", encoder->GetDirection());	
}

void OI::DisplayPIDController(PIDController *controller)
{
	SmartDashboard *sd = getSmartDashboard();

	sd->PutDouble("Controller result", controller->Get());
	sd->PutDouble("Controller error2", controller->GetError());
	
	sd->PutDouble("Controller P", controller->GetP());
	sd->PutDouble("Controller I", controller->GetI());
	sd->PutDouble("Controller D", controller->GetD());
	sd->PutDouble("Controller setpoint", controller->GetSetpoint());

}
