#include "ThrowerV2Command.h"

#define WAIT_FOR_THROW_SECS (0.25)
#define MINIMUM_THROW_TIME (.0)
#define MAX_THROW_TIME (.2)
#define THROW_TIME_PER_INCREMENT ((MAX_THROW_TIME - MINIMUM_THROW_TIME) / 100.0)

// This is the number of milliseconds per iteration on the robot, used
// below to wait precise amount of time.
#define CYCLE_TIME .02

ThrowerV2Command::ThrowerV2Command() : CommandBase("ThrowerV2Command") {
	Requires(throwerSubsystem);
	throwSolenoidTimer = new Timer();
	this->throwTime = -1;
	this->useThrowerSetting = true;
}

ThrowerV2Command::ThrowerV2Command(float throwTime) : CommandBase("ThrowerV2Command") {
	Requires(throwerSubsystem);
	throwSolenoidTimer = new Timer();
	this->throwTime = throwTime;
	this->useThrowerSetting = false;
}

// Called just before this Command runs the first time
void ThrowerV2Command::Initialize() {
	finished = false;
	retracting = false;
	if (this->useThrowerSetting)
	{
		printf("Setting throw power from setting %d.\n", this->throwerPower);
		this->throwTime = MINIMUM_THROW_TIME + (THROW_TIME_PER_INCREMENT * this->throwerPower);
	}
	else
	{
		printf("Using preset throw time.\n");
	}
	throwerSubsystem->StartThrow();
	throwSolenoidTimer->Reset();
	throwSolenoidTimer->Start();
	printf("Thrower starting.  Time is %f\n", throwTime);
}

// Called repeatedly when this Command is scheduled to run
void ThrowerV2Command::Execute() {
	double elapsedTime = throwSolenoidTimer->Get();

	if (!retracting) {
		if (elapsedTime - CYCLE_TIME >= throwTime) {
			printf("Thrower stopping.  Elapsed time is %f, waiting %f\n", elapsedTime, CYCLE_TIME);
			
			while (elapsedTime < throwTime)
			{
				elapsedTime = throwSolenoidTimer->Get();
			}
			printf("Done waiting.  Elapsed time is %f\n", elapsedTime);
			throwerSubsystem->StopThrow();
			retracting = true;
			throwSolenoidTimer->Stop();
			throwSolenoidTimer->Reset();
			throwSolenoidTimer->Start();

		}
	} else {
		if (elapsedTime >= WAIT_FOR_THROW_SECS) {
			printf("Done waiting for retract.  Elapsed time is %f\n", elapsedTime);
			throwerSubsystem->Retract();
			finished = true;
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ThrowerV2Command::IsFinished() {
	return finished;
}

// Called once after isFinished returns true
void ThrowerV2Command::End() {
	throwSolenoidTimer->Stop();
	printf("Thrower finished.");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ThrowerV2Command::Interrupted() {
}
