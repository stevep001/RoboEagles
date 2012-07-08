#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/AutoBasketsRampCommandGroup.h"
#include "Commands/AutoRampBasketsCommandGroup.h"
#include "Commands/BallEjectBackupRightCommandGroup.h"
#include "CommandBase.h"

class CommandBasedRobot : public IterativeRobot {
private:
	Command *autonomousCommand;
	
	virtual void RobotInit() {
		printf("RobotInit starting.\n");
		CommandBase::init();
		printf("RobotInit completed.\n");
	}
	
	virtual void AutonomousInit() {
		printf("AutonomousInit starting.\n");
		printf("Running program %d", CommandBase::autonomousProgram);
		
#define RT_RAMP_TURN_ANGLE 160
		
		if (CommandBase::autonomousProgram == ABRT_IMMEDIATE_MODE)
		{	
			autonomousCommand = new AutoBasketsRampCommandGroup(0, RT_RAMP_TURN_ANGLE);
		}
		else if (CommandBase::autonomousProgram == ABRT_2SEC_MODE)
		{
			autonomousCommand = new AutoBasketsRampCommandGroup(2, RT_RAMP_TURN_ANGLE);
		}
		else if (CommandBase::autonomousProgram == ABRT_4SEC_MODE)
		{
			autonomousCommand = new AutoBasketsRampCommandGroup(4, RT_RAMP_TURN_ANGLE);
		}
		else if (CommandBase::autonomousProgram == ABRT_6SEC_MODE)
		{
			autonomousCommand = new AutoBasketsRampCommandGroup(6, RT_RAMP_TURN_ANGLE);
		}
		else if (CommandBase::autonomousProgram == ABRT_8SEC_MODE)
		{
			autonomousCommand = new AutoBasketsRampCommandGroup(8, RT_RAMP_TURN_ANGLE);
		}
		else if (CommandBase::autonomousProgram == ABRM_IMMEDIATE_MODE)
		{
			autonomousCommand = new AutoBasketsRampCommandGroup(0, 225);
		}
		else if (CommandBase::autonomousProgram == ABRM_2SEC_MODE)
		{
			autonomousCommand = new AutoBasketsRampCommandGroup(2, 225);
		}
		else if (CommandBase::autonomousProgram == ABRM_4SEC_MODE)
		{
			autonomousCommand = new AutoBasketsRampCommandGroup(4, 225);
		}
		else if (CommandBase::autonomousProgram == ABRM_6SEC_MODE)
		{
			autonomousCommand = new AutoBasketsRampCommandGroup(6, 225);
		}
		else if (CommandBase::autonomousProgram == ABRM_8SEC_MODE)
		{
			autonomousCommand = new AutoBasketsRampCommandGroup(8, 225);
		}
		else if (CommandBase::autonomousProgram == ABLM_IMMEDIATE_MODE)
		{
			autonomousCommand = new AutoBasketsRampCommandGroup(0, -225);
		}
		else if (CommandBase::autonomousProgram == ABLM_2SEC_MODE)
		{
			autonomousCommand = new AutoBasketsRampCommandGroup(2, -225);
		}
		else if (CommandBase::autonomousProgram == ABLM_4SEC_MODE)
		{
			autonomousCommand = new AutoBasketsRampCommandGroup(4, -225);
		}
		else if (CommandBase::autonomousProgram == ABLM_6SEC_MODE)
		{
			autonomousCommand = new AutoBasketsRampCommandGroup(6, -225);
		}
		else if (CommandBase::autonomousProgram == ABLM_8SEC_MODE)
		{
			autonomousCommand = new AutoBasketsRampCommandGroup(8, -225);
		}
		else if (CommandBase::autonomousProgram == AUTO_RAMP_BASKETS_MODE)
		{
			autonomousCommand = new AutoRampBasketsCommandGroup();
		} 
		else if (CommandBase::autonomousProgram == BALL_EJECT_MODE)
		{
			autonomousCommand = new BallEjectBackupRightCommandGroup();
		} 
		else if (CommandBase::autonomousProgram == AUTO_DO_NOTHING_MODE)
		{
			autonomousCommand = new PrintCommand("Do nothing autonomous selected");
		}
		else
		{
			autonomousCommand = new PrintCommand("Unknown autonomous mode.\n");
		}
		
		autonomousCommand->Start();
		printf("AutonomousInit completing.\n");
	}
	
	virtual void AutonomousPeriodic() {
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TeleopInit() {
		printf("TeleopInit starting.\n");
		if (autonomousCommand != NULL && autonomousCommand->IsRunning()) {
			printf("Cancelling autonomous command\n");
			autonomousCommand->Cancel();
		}
		printf("TeleopInit completing.\n");

	}
	
	virtual void TeleopPeriodic() {
		Scheduler::GetInstance()->Run();
	}
	
	virtual void DisabledInit() {
		printf("DisabledInit starting.\n");
		printf("DisabledInit completing.\n");
	}
	
	virtual void DisabledPeriodic() {
	}
};

START_ROBOT_CLASS(CommandBasedRobot);

