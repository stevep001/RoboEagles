#include "Chassis.h"
#include "../Robotmap.h"
#include "../Commands/DriveWithJoystick.h"
#include "../Commands/RampDriveCommand.h"

Chassis::Chassis() : Subsystem("Chassis") {
	printf("Chassis constructor");
	leftCoastBrakeOutput = new DigitalOutput(LEFT_BRAKE_CHANNEL);
	leftCoastBrakeOutput->Set(JAGUAR_COAST);
	rightCoastBrakeOutput = new DigitalOutput(RIGHT_BRAKE_CHANNEL);
	rightCoastBrakeOutput->Set(JAGUAR_COAST);
	drive = new RobotDrive(DRIVE_MOTOR_R_PWM, DRIVE_MOTOR_L_PWM);
	drive->SetInvertedMotor(drive->kRearRightMotor, true);
	drive->SetSafetyEnabled(false);
	printf("Chassis constructor completed");
}

void Chassis::InitDefaultCommand() {
	SetDefaultCommand(new DriveWithJoystick());
}

void Chassis::MakeJoystickDriveDefault() {
	SetDefaultCommand(new DriveWithJoystick());
}

void Chassis::MakeRampDriveDefault() {
	SetDefaultCommand(new RampDriveCommand());
}

void Chassis::goStraight(float rate) {
	drive->ArcadeDrive(rate, 0.0);
}
void Chassis::turnLeft(float rate) {
	drive->ArcadeDrive(0.0, rate);
}
void Chassis::turnRight(float rate) {
	drive->ArcadeDrive(0.0, -rate);
}
void Chassis::stop(){
	drive->ArcadeDrive(0.0, 0.0);
}

void Chassis::tankDrive(double left, double right) {
	drive->TankDrive(left, right); 
}
void Chassis::driveWithJoystick(Joystick *stick) {
	drive->ArcadeDrive(stick);
}

void Chassis::driveWithKinectStick(KinectStick *stick){
	drive->ArcadeDrive(stick);
}

void Chassis::enableBrakeMode() {
	leftCoastBrakeOutput->Set(JAGUAR_BRAKE);
	rightCoastBrakeOutput->Set(JAGUAR_BRAKE);
}

void Chassis::disableBrakeMode() {
	leftCoastBrakeOutput->Set(JAGUAR_COAST);
	rightCoastBrakeOutput->Set(JAGUAR_COAST);
}

