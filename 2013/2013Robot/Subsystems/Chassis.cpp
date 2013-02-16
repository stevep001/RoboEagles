#include "Chassis.h"
#include "../Robotmap.h"
#include "../Commands/DriveWithJoystickCommand.h"


Chassis::Chassis() : Subsystem("Chassis") {
	printf("Chassis: constructor started");
	this->drive = new RobotDrive(PWM_SLOT, DRIVE_MOTOR_R_1, PWM_SLOT, DRIVE_MOTOR_L_1);
	this->drive->SetInvertedMotor(drive->kRearRightMotor, true);
	this->drive->SetSafetyEnabled(false);
	
	printf("Chassis: constructor completed");
	
}
    
void Chassis::InitDefaultCommand() {
	SetDefaultCommand(new DriveWithJoystickCommand());
}

void Chassis::Drive(Joystick *stick) {
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
