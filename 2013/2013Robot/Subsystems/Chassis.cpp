#include "Chassis.h"
#include "../Robotmap.h"
#include "../Commands/DriveWithJoystickCommand.h"


Chassis::Chassis() : Subsystem("Chassis") {
	printf("Chassis: constructor started");
	this->drive = new RobotDrive(DRIVE_MOTOR_R_1, DRIVE_MOTOR_L_1);
	this->drive->SetInvertedMotor(drive->kRearRightMotor, true);
	this->drive->SetSafetyEnabled(false);
	this->leftEncoder = new Encoder(LEFT_GEARBOX_ENCODER_1, LEFT_GEARBOX_ENCODER_2, false, CounterBase::k4X);
	this->leftEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->leftEncoder->SetDistancePerPulse(1);
	this->leftEncoder->SetMaxPeriod(1.0);
	this->leftEncoder->Reset();
	this->leftEncoder->Start();
	
	this->rightEncoder = new Encoder(RIGHT_GEARBOX_ENCODER_1, RIGHT_GEARBOX_ENCODER_2, false, CounterBase::k4X);
	this->rightEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->rightEncoder->SetDistancePerPulse(1);
	this->rightEncoder->SetMaxPeriod(1.0);
	this->rightEncoder->Reset();
	this->rightEncoder->Start();
	
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
