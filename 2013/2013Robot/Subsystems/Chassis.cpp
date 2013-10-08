#include "Chassis.h"
#include "../Robotmap.h"
#include "../Commands/DriveWithJoystickCommand.h"
#include "stdlib.h"


Chassis::Chassis() : Subsystem("Chassis") {
	printf("Chassis: constructor started\n");
	
	this->leftMotor = new Talon(PWM_SLOT, DRIVE_MOTOR_L_1);
	this->rightMotor = new Talon(PWM_SLOT, DRIVE_MOTOR_R_1);
	this->drive = new RobotDrive(this->leftMotor, this->rightMotor);
	this->drive->SetInvertedMotor(drive->kRearRightMotor, true);
	this->drive->SetInvertedMotor(drive->kRearLeftMotor, true);
	this->drive->SetSafetyEnabled(false);
	
	printf("Chassis: constructor completed\n");
	
}
    
void Chassis::InitDefaultCommand() {
	SetDefaultCommand(new DriveWithJoystickCommand());
}

void Chassis::Drive(Joystick *stick) {
	// TODO need to trim these values below .1
	drive->ArcadeDrive(stick);
}

void Chassis::Stop(){
	drive->ArcadeDrive(0.0, 0.0);
}

void Chassis::MoveForward(float rate) {
	drive->ArcadeDrive(rate, 0.0);
}
void Chassis::TurnLeft(float rate) {
	drive->ArcadeDrive(0.0, rate);
}

void Chassis::TurnRight(float rate) {
	drive->ArcadeDrive(0.0, -rate);
}

void Chassis::TankDrive(float rateLeft, float rateRight){
	drive->TankDrive(rateLeft, rateRight);
}

RobotDrive *Chassis::GetRobotDrive() {
	return this->drive;
}

SpeedController *Chassis::GetLeftMotor() {
	return this->leftMotor;
}

SpeedController *Chassis::GetRightMotor() {
	return this->rightMotor;
}
