#include "ShooterTiltSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/MaintainShooterPositionCommand.h"

// TODO: this is a guess, need actual value
#define TILT_SPEED (0.2)
#define MIN_ANGLE	0
#define MAX_ANGLE	90
#define NUM_ROTATIONS_TO_LIFT_VERTICAL	8


ShooterTiltSubsystem::ShooterTiltSubsystem() : Subsystem("ShooterTiltSubsystem") {
	printf("ShooterTiltSubsystem: constructor started\n");
	this->tiltEncoder = new Encoder(TILT_ENCODER_SLOT, TILT_ENCODER_1, TILT_ENCODER_SLOT, TILT_ENCODER_2, false, CounterBase::k4X);
	this->tiltJaguar = new Jaguar(TILT_MOTOR);
	this->tiltLowerLimit = new DigitalInput(TILT_LOW_LIMIT_SWITCH_SLOT, TILT_LOW_LIMIT_SWITCH);
	this->tiltUpperLimit = new DigitalInput(TILT_HIGH_LIMIT_SWITCH_SLOT, TILT_HIGH_LIMIT_SWITCH);
	
	this->tiltEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->tiltEncoder->SetDistancePerPulse(1);
	this->tiltEncoder->SetMaxPeriod(1.0);
	this->tiltEncoder->Reset();
	this->tiltEncoder->Start();
	
	this->currentAngle = 0;
	
	float pGain = .0013;
	float iGain = .0002;
	float dGain = 0;

	this->pidController = new PIDController(pGain, iGain, dGain, 
			this->tiltEncoder, this->tiltJaguar);
	
	// TODO: need to calculate actual input range here
	this->pidController->SetInputRange(0, 500);
	// This is the range of the output device.  For a motor controller this is typically
	// -1 to 1.
	this->pidController->SetOutputRange(-1, 1);
	this->pidController->SetSetpoint(0);

	this->pidController->Enable(); // start calculating PIDOutput values
	printf("ShooterTiltSubsystem: constructor completed\n");
}
    
void ShooterTiltSubsystem::InitDefaultCommand() {
}

void ShooterTiltSubsystem::SetAngle(float desiredAngle)
{
	if (desiredAngle > MAX_ANGLE)
		this->currentAngle = MAX_ANGLE;
	else if (desiredAngle < MIN_ANGLE)
		this->currentAngle = MIN_ANGLE;
	else
		this->currentAngle = desiredAngle;
	
	float setpoint = (this->currentAngle / 90) * NUM_ROTATIONS_TO_LIFT_VERTICAL;
	this->pidController->SetSetpoint(setpoint);
}

void ShooterTiltSubsystem::Stop()
{
	this->tiltJaguar->Set(0);
}

void ShooterTiltSubsystem::IncreaseTilt(float amountToIncrease)
{
	this->SetAngle(this->currentAngle + amountToIncrease);
}

void ShooterTiltSubsystem::DecreaseTilt(float amountToDecrease)
{
	this->SetAngle(this->currentAngle - amountToDecrease);
}
