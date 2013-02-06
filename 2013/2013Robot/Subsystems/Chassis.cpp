#include "Chassis.h"
#include "../Robotmap.h"
#include "../Commands/DriveWithJoystick.h"


Chassis::Chassis() : Subsystem("Chassis") {
	printf("Chassis constructor");
	drive = new RobotDrive(DRIVE_MOTOR_R_PWM, DRIVE_MOTOR_L_PWM);
	drive->SetInvertedMotor(drive->kRearRightMotor, true);
	drive->SetSafetyEnabled(false);
	printf("Chassis constructor completed");
	
}
    
void Chassis::InitDefaultCommand() {
	SetDefaultCommand(new DriveWithJoystick());
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

