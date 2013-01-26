#include "PrototypingSubsystem.h"
#include "../Commands/RPMHoldingCommand.h"
#include "../commands/PositionHoldingCommand.h"
#include "../Robotmap.h"


PrototypingSubsystem::PrototypingSubsystem() : Subsystem("ProtypingSubsystem") {
	printf("PrototypingSubsystem constructor\n");

	int a_channel = 1;
	int b_channel = 2;
	
	printf("PrototypingSubsystem before jaguar setup\n");
	motor = new Jaguar(1);
	printf("PrototypingSubsystem before motor encoder\n");
	motorEncoder = new Encoder(a_channel, b_channel, false, CounterBase::k4X);
	printf("PrototypingSubsystem after motor encoder\n");

	motorEncoder->SetPIDSourceParameter(Encoder::kDistance);
    motorEncoder->SetDistancePerPulse(1);
    motorEncoder->SetMaxPeriod(1.0);
	printf("PrototypingSubsystem before encoder start\n");

    motorEncoder->Start();
	printf("PrototypingSubsystem constructor complete\n");


}
    
void PrototypingSubsystem::InitDefaultCommand() {
	printf("PrototypingSubsystem InitDefaultCommand\n");
	//SetDefaultCommand(new RPMHoldingCommand());
	//SetDefaultCommand(new PositionHoldingCommand());
}

Jaguar* PrototypingSubsystem::GetMotor()
{
	return motor;
}

Encoder * PrototypingSubsystem::GetMotorEncoder()
{
	return motorEncoder;
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

