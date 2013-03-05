#include "SensorSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/SensorDisplayCommand.h"

SensorSubsystem::SensorSubsystem() : Subsystem("SensorSubsystem") {
	printf("Sensor subsystem initializing\n");
	this->loaderFrisbeeDetector = new DigitalInput(1, LOADER_FRISBEE_DETECTOR_PORT);
	this->loaderLowLimitSwitch = new DigitalInput(1, LOADER_LOW_LIMIT_SWITCH);
	
	this->panLiftEncoder = new Encoder(PAN_LIFT_ENCODER_1, PAN_LIFT_ENCODER_2, false, CounterBase::k4X);
	
	this->panLiftEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->panLiftEncoder->SetDistancePerPulse(1);
	this->panLiftEncoder->SetMaxPeriod(1.0);
	this->panLiftEncoder->Reset();
	this->panLiftEncoder->Start();
	printf("Sensor subsystem initialized\n");
}
    
void SensorSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new SensorDisplayCommand());
}

bool SensorSubsystem::IsFrisbeeInLoader() {
	return this->loaderFrisbeeDetector->Get() == 0;
}

bool SensorSubsystem::IsLoaderAtLowLimit() {
	return this->loaderLowLimitSwitch->Get() == 0;
}

int SensorSubsystem::GetPanLiftEncoderCount() {
	return this->panLiftEncoder->Get();
}

Encoder* SensorSubsystem::GetPanLiftEncoder() {
	return this->panLiftEncoder;
}
