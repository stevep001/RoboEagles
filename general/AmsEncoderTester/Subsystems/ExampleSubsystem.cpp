#include "ExampleSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/ExampleCommand.h"

ExampleSubsystem::ExampleSubsystem() : Subsystem("ExampleSubsystem") {
	this->motorController = new Jaguar(1, 1);
	this->relay1 = new Relay(1, 1);
	this->encoder = new Encoder(4, 5, false, CounterBase::k4X);
	this->encoder->SetDistancePerPulse(1);
	this->encoder->SetMaxPeriod(1.0);
	this->encoder->Start();
	this->magDec = new DigitalInput(6);
	this->magInc = new DigitalInput(7);
}
    
void ExampleSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ExampleCommand());
}

void ExampleSubsystem::SetMotorPower(float power)
{
	this->relay1->Set(Relay::kOn);
	this->motorController->Set(power);
	printf("power set to %f\n", power);
}

int ExampleSubsystem::GetCount()
{
	return this->encoder->Get();
}

bool ExampleSubsystem::GetMagDec()
{
	return this->magDec->Get() == 0;
}

bool ExampleSubsystem::GetMagInc()
{
	return this->magInc->Get() == 0;
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

