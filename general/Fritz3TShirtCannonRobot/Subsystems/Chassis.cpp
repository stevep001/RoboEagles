#include "Chassis.h"
#include "../Robotmap.h"
#include "../Commands/DriveWithJoystick.h"
//#include "../Commands/RampDriveCommand.h"

/**
 * Controls the undercarriage of the robot.
 */
Chassis::Chassis() : Subsystem("Chassis") {
	printf("Chassis constructor");

	drive = new RobotDrive(DRIVE_MOTOR_R_PWM, DRIVE_MOTOR_L_PWM);
	drive->SetInvertedMotor(drive->kRearRightMotor, true);
	drive->SetInvertedMotor(drive->kRearLeftMotor, true);
	drive->SetSafetyEnabled(false);
	printf("Chassis constructor completed\n");
}

void Chassis::InitDefaultCommand() {
	SetDefaultCommand(new DriveWithJoystick());
}

void Chassis::MakeJoystickDriveDefault() {
	SetDefaultCommand(new DriveWithJoystick());
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

