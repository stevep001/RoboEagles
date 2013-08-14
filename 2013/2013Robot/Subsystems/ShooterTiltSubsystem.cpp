#include "ShooterTiltSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/ShooterTiltSupervisorCommand.h"
#include "../CommandBase.h"

/*
 * This subsystem teams with the ShooterTiltSupervisorCommand to 
 * manage the angle of the shooting tilt.
 */
ShooterTiltSubsystem::ShooterTiltSubsystem() : PIDSubsystem("ShooterTiltSubsystem", pGain, iGain, dGain) {
	printf("ShooterTiltSubsystem: constructor started\n");
	this->tiltMotor = new Victor(PWM_SLOT, TILT_MOTOR);
	this->currentAngle = 0;
	
	this->tiltEncoder = new Encoder(TILT_ENCODER_SLOT, TILT_ENCODER_1, TILT_ENCODER_SLOT, TILT_ENCODER_2, 
			true, CounterBase::k4X);
	this->tiltEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->tiltEncoder->SetDistancePerPulse(1);
	this->tiltEncoder->SetMaxPeriod(1.0);
	this->tiltEncoder->Reset();
	this->tiltEncoder->Start();
	
	LiveWindow::GetInstance()->AddActuator("ShooterTiltUbsystem", "PID Controller", this->GetPIDController());
	this->mode = ShooterTiltSubsystem::Initializing;
	printf("ShooterTiltSubsystem: constructor completed\n");
}
    
void ShooterTiltSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new ShooterTiltSupervisorCommand());
}

void ShooterTiltSubsystem::SetMode(ShooterTiltSubsystem::ShooterTiltMode mode)
{
	this->mode = mode;
}

/*
 * Returns the mode of the shooting tilt system.
 */
ShooterTiltSubsystem::ShooterTiltMode ShooterTiltSubsystem::GetMode()
{
	return this->mode;
}

SpeedController* ShooterTiltSubsystem::GetMotor()
{
	return this->tiltMotor;
}

/*
 * Sets the desired angle of the tilt.  This is clipped to zero on the low side
 * and our max angle on the top side.
 */
void ShooterTiltSubsystem::SetAngle(float desiredAngle)
{
	if (desiredAngle > MAX_TILT_ANGLE)
		this->currentAngle = MAX_TILT_ANGLE;
	else if (desiredAngle < MIN_TILT_ANGLE)
		this->currentAngle = MIN_TILT_ANGLE;
	else
		this->currentAngle = desiredAngle;
	printf("Angle set to %f\n", desiredAngle);
	SmartDashboard::PutNumber("Shooter tilt angle", this->currentAngle);
}

float ShooterTiltSubsystem::GetAngle()
{
	return this->currentAngle;
}

void ShooterTiltSubsystem::IncreaseTilt(float amountToIncrease)
{
	this->SetAngle(this->currentAngle + amountToIncrease);
}

void ShooterTiltSubsystem::DecreaseTilt(float amountToDecrease)
{
	this->SetAngle(this->currentAngle - amountToDecrease);
}

double ShooterTiltSubsystem::ReturnPIDInput() {
	return tiltEncoder->PIDGet();
}
void ShooterTiltSubsystem::UsePIDOutput(double output) {
	this->tiltMotor->PIDWrite(output);
}

PIDController *ShooterTiltSubsystem::GetTiltPIDController() {
	return this->GetPIDController();
}

Encoder *ShooterTiltSubsystem::GetTiltEncoder() {
	return this->tiltEncoder;
}
