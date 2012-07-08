#include "BallLoaderSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/BallLoaderManualCommand.h"
#include "../Commands/BallLoaderAutomatedCommand.h"


/**
 * Controls the belt/flap ball loading subsystem
 */
BallLoaderSubsystem::BallLoaderSubsystem() : Subsystem("BallLoaderSubsystem") {
	printf("BallLoaderSubsystem constructor\n");
	flapSolenoidDown = new Solenoid(FLAP_SOLENOID_DOWN);
	flapSolenoidUp = new Solenoid(FLAP_SOLENOID_UP);
	beltJag = new Jaguar(BELT_MOTOR_PWM);
	sweeperJag = new Jaguar(SWEEPER_MOTOR_PWM);
	
//	beltRelay = new Relay(BELT_RELAY_CHANNEL);
//	underBeltRelay = new Relay(UNDERBELT_RELAY_CHANNEL);
	
	
	BeltOff();
	FlapUp();
}
    
void BallLoaderSubsystem::InitDefaultCommand() {
	printf("BallLoaderSubsystem initializing\n");
	
//	SetDefaultCommand(new BallLoaderManualCommand());   -----------
	
	SetDefaultCommand(new BallLoaderAutomatedCommand());
	printf("BallLoaderSubsystem initialized\n");
}

void BallLoaderSubsystem::BeltUp() {
	//printf("Belt Up \n");
	beltJag->SetSpeed(1);
	sweeperJag->SetSpeed(1);
}

void BallLoaderSubsystem::BeltDown() {
	//printf("Belt Down\n");
	beltJag->SetSpeed(-1);
	sweeperJag->SetSpeed(-1);
}

void BallLoaderSubsystem::BeltOff() {
	//printf("Belt Off\n");
	beltJag->SetSpeed(0);
	sweeperJag->SetSpeed(0);
}

void BallLoaderSubsystem::FlapUp() {
	flapSolenoidDown->Set(false);
	flapSolenoidUp->Set(true);
}

void BallLoaderSubsystem::FlapDown() {
	flapSolenoidUp->Set(false);
	flapSolenoidDown->Set(true);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
