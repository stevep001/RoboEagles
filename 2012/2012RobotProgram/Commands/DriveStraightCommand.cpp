#include "DriveStraightCommand.h"

DriveStraightCommand::DriveStraightCommand(float time, float speed) : CommandBase("DriveStraightCommand") {
	Requires(chassis);
	this->time = time;
	this->speed = speed;
	this->drivingTimer = new Timer();
}

// Called just before this Command runs the first time
void DriveStraightCommand::Initialize() {
	this->drivingTimer->Reset();
	this->drivingTimer->Start();
	printf("Driving straight: time %f, speed %f\n", this-> time, this->speed);}

// Called repeatedly when this Command is scheduled to run
void DriveStraightCommand::Execute() {
	chassis->goStraight(this->speed);

}


bool DriveStraightCommand::IsFinished() {
	return this->drivingTimer->Get() > this -> time;
}

// Called once after isFinished returns true
void DriveStraightCommand::End() {
	chassis->goStraight(0);
	this->drivingTimer->Stop();
	printf("DriveStraightCommand completed.\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraightCommand::Interrupted() {
}
