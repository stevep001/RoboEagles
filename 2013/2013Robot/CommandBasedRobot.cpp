#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/ExampleCommand.h"
#include "Commands/CenterAutonomousCommandGroup.h"
#include "Commands/LeftPyramidAutonomousCommandGroup.h"
//#include "Commands/ShooterTiltSupervisorCommand.h"
#include "CommandBase.h"

class CommandBasedRobot : public IterativeRobot {
private:
	Command *autonomousCommand;
	Command *shooterTiltCommand;
	LiveWindow *lw;
	
	virtual void RobotInit() {
		printf("3081 Robot code compiled on %s at %s\n",__DATE__, __TIME__);
		CommandBase::init();
		lw = LiveWindow::GetInstance();
		this->autonomousCommand = NULL;
		//this->shooterTiltCommand = NULL;
		//SmartDashboard::PutData(Scheduler::GetInstance());
	}
	
	virtual void AutonomousInit() {
		printf("Starting autonomous initialization\n");
		//if(this->shooterTiltCommand != NULL) {
		//			this->shooterTiltCommand->Cancel();
		//		}
				
		if (DriverStation::GetInstance()->GetDigitalIn(1))
		{
			this->autonomousCommand = new CenterAutonomousCommandGroup();
		}
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
		//if(this->shooterTiltCommand != NULL) {
		//	this->shooterTiltCommand->Cancel();
		//}
		
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
		//this->shooterTiltCommand = new ShooterTiltSupervisorCommand();
		//this->shooterTiltCommand->Start();
	}
	
	virtual void TestPeriodic() {
		lw->Run();
	}
};

START_ROBOT_CLASS(CommandBasedRobot);

