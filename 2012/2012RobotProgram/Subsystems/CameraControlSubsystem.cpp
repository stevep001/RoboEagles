#include "CameraControlSubsystem.h"
#include "../Robotmap.h"

CameraControlSubsystem::CameraControlSubsystem() : Subsystem("CameraControlSubsystem") {
	cameraServo = new Servo(CAMERA_SERVO_PWM);
	cameraServo->Set(0.5);
}
    
void CameraControlSubsystem::InitDefaultCommand() {
}

void CameraControlSubsystem::Move(float pos){
	printf("Camera position set to %f\n", pos);
	cameraServo->Set(pos);
}
