#include "SensorSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/SensorDisplayCommand.h"


/**
 * This subsystem is for shared sensors
 */
SensorSubsystem::SensorSubsystem() : Subsystem("SensorSubsystem") {
	printf("SensorSubsystem: constructor starting\n");
	this->horizontalGyro = new Gyro(HORIZONTAL_GYRO_CHANNEL);
	this->horizontalGyro->SetSensitivity(0.007);
	
	this->tiltEncoderMagDec = new DigitalInput(TILT_ENCODER_SLOT, TILT_ENCODER_MAGDEC);
	this->tiltEncoderMagInc = new DigitalInput(TILT_ENCODER_SLOT, TILT_ENCODER_MAGINC);
	printf("SensorSubsystem: constructor completed\n");
}
    
void SensorSubsystem::InitDefaultCommand() {
	this->SetDefaultCommand(new SensorDisplayCommand());
}

float SensorSubsystem::GetHorizontalAngle() {
	return horizontalGyro->GetAngle();
}

bool SensorSubsystem::GetTiltEncoderMagDec() {
	return this->tiltEncoderMagInc->Get() == 1;
}

bool SensorSubsystem::GetTiltEncoderMagInc() {
	return this->tiltEncoderMagInc->Get() == 1;
}
