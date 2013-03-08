#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/ExampleCommand.h"
#include "Commands/CenterAutonomousCommandGroup.h"
#include "Commands/LeftPyramidAutonomousCommandGroup.h"
#include "CommandBase.h"

class CommandBasedRobot : public IterativeRobot {
private:
	Command *autonomousCommand;
	LiveWindow *lw;
	
	virtual void RobotInit() {
		CommandBase::init();
		lw = LiveWindow::GetInstance();
		this->autonomousCommand = NULL;
	}
	
	virtual void AutonomousInit() {
		printf("Starting autonomous initialization\n");
		this->autonomousCommand = new CenterAutonomousCommandGroup();
		// TODO select autonomous here
		this->autonomousCommand->Start();
		printf("Autonomous initialization completed.\n");
	}
	
	virtual void AutonomousPeriodic() {
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TeleopInit() {
		printf("Starting teleop initialization\n");
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (this->autonomousCommand != NULL)
		{
			this->autonomousCommand->Cancel();
		}
		printf("Teleop initialization complete\n");
	}
	
	virtual void TeleopPeriodic() {
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TestPeriodic() {
		lw->Run();
	}
};

START_ROBOT_CLASS(CommandBasedRobot);

