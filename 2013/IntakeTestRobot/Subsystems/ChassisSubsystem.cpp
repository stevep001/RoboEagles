#include "ChassisSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/DriveWithJoystickCommand.h"

ChassisSubsystem::ChassisSubsystem() : Subsystem("ChassisSubsystem") {
	printf("Chassis: constructor started\n");
	
	this->leftMotor = new Talon(PWM_SLOT, DRIVE_MOTOR_L_1);
	this->rightMotor = new Talon(PWM_SLOT, DRIVE_MOTOR_R_1);
	this->drive = new RobotDrive(this->leftMotor, this->rightMotor);
	this->drive->SetInvertedMotor(drive->kRearRightMotor, true);
	this->drive->SetInvertedMotor(drive->kRearLeftMotor, true);
	this->drive->SetSafetyEnabled(false);
	
	printf("Chassis: constructor completed\n");	
}
    
void ChassisSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new DriveWithJoystickCommand());
}

void ChassisSubsystem::Drive(Joystick *stick) {
	// TODO need to trim these values below .1
	drive->ArcadeDrive(stick);
}

void ChassisSubsystem::Stop(){
	drive->ArcadeDrive(0.0, 0.0);
}
