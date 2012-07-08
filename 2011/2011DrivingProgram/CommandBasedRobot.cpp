#include "WPILib.h"
#include "Commands/Command.h"
#include "CommandBase.h"
#include "SmartDashboard/SmartDashboard.h"

class CommandBasedRobot : public IterativeRobot {
private:
	//Command *autonomousCommand = NULL;
	Command *drivingCommand;
	
	virtual void RobotInit() {
		CommandBase::init();
//		SmartDashboard.putData(CommandBase::chassis);
	}
	
	virtual void AutonomousInit() {
	}
	
	virtual void AutonomousPeriodic() {
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TeleopInit() {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
		// autonomousCommand->Cancel();
		
		
	}
	
	virtual void TeleopPeriodic() {
		Scheduler::GetInstance()->Run();
	}
};

START_ROBOT_CLASS(CommandBasedRobot);

