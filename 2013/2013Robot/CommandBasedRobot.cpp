#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/ExampleCommand.h"
#include "Commands/CenterAutonomousCommandGroup.h"
#include "Commands/FrontPyramidHighGoalCommandGroup.h"
#include "Commands/FrontPyramidMiddleGoalCommandGroup.h"
#include "Commands/AutoDoNothingCommand.h"
#include "CommandBase.h"

class CommandBasedRobot : public IterativeRobot {
private:
	Command *autonomousCommand;
	LiveWindow *lw;
	SendableChooser *chooser;
	
	virtual void RobotInit() {
		printf("3081 Robot code compiled on %s at %s\n",__DATE__, __TIME__);
		CommandBase::init();
		lw = LiveWindow::GetInstance();
		this->chooser = new SendableChooser();
		
		this->chooser->AddDefault("Center Autonomous", new CenterAutonomousCommandGroup());
		this->chooser->AddObject("Right Front Py. High Goal", new FrontPyramidHighGoalCommandGroup(FrontPyramidHighGoalCommandGroup::kRight));
		this->chooser->AddObject("Left Front Py. High Goal", new FrontPyramidHighGoalCommandGroup(FrontPyramidHighGoalCommandGroup::kLeft));
		this->chooser->AddObject("Pyramid Front Side Middle Goal", new FrontPyramidMiddleGoalCommandGroup());
		this->chooser->AddObject("Do nothing", new AutoDoNothingCommand());
		this->autonomousCommand = NULL;
		SmartDashboard::PutData("Autonomus Mode Chooser", chooser);
	}
	
	virtual void AutonomousInit() {
		printf("Starting autonomous initialization\n");
				
		if (DriverStation::GetInstance()->GetDigitalIn(1))
		{
			this->autonomousCommand = (Command *) this->chooser->GetSelected();
			this->autonomousCommand->Start();
		}
		
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
	
	virtual void TestInit() {
	}
	
	virtual void TestPeriodic() {
		lw->Run();
	}
};

START_ROBOT_CLASS(CommandBasedRobot);
