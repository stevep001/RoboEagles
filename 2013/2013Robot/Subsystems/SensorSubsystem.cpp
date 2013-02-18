#include "SensorSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/SensorDisplayCommand.h"
#include "../CommandBase.h"


/**
 * This subsystem is for shared sensors
 */
SensorSubsystem::SensorSubsystem() : Subsystem("SensorSubsystem") {
	printf("SensorSubsystem: constructor starting\n");
	this->horizontalGyro = new Gyro(HORIZONTAL_GYRO_CHANNEL);
	this->horizontalGyro->SetSensitivity(0.007);
	
	this->tiltEncoderMagDec = new DigitalInput(TILT_ENCODER_SLOT, TILT_ENCODER_MAGDEC);
	this->tiltEncoderMagInc = new DigitalInput(TILT_ENCODER_SLOT, TILT_ENCODER_MAGINC);
	
	this->leftEncoder = new Encoder(LEFT_GEARBOX_ENCODER_1, LEFT_GEARBOX_ENCODER_2, false, CounterBase::k4X);
	this->leftEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->leftEncoder->SetDistancePerPulse(1);
	this->leftEncoder->SetMaxPeriod(1.0);
	this->leftEncoder->Reset();
	this->leftEncoder->Start();
	
	this->rightEncoder = new Encoder(RIGHT_GEARBOX_ENCODER_1, RIGHT_GEARBOX_ENCODER_2, false, CounterBase::k4X);
	this->rightEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->rightEncoder->SetDistancePerPulse(1);
	this->rightEncoder->SetMaxPeriod(1.0);
	this->rightEncoder->Reset();
	this->rightEncoder->Start();
	
	this->tiltEncoder = new Encoder(TILT_ENCODER_SLOT, TILT_ENCODER_1, TILT_ENCODER_SLOT, TILT_ENCODER_2, 
			true, CounterBase::k4X);
	this->tiltEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->tiltEncoder->SetDistancePerPulse(1);
	this->tiltEncoder->SetMaxPeriod(1.0);
	this->tiltEncoder->Reset();
	this->tiltEncoder->Start();
	
	this->shooterEncoder = new Encoder(SHOOTER_WHEEL_ENCODER_SLOT, SHOOTER_WHEEL_ENCODER_1, 
			SHOOTER_WHEEL_ENCODER_SLOT, SHOOTER_WHEEL_ENCODER_2, false, CounterBase::k1X);
	this->shooterEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->shooterEncoder->SetDistancePerPulse(1);
	this->shooterEncoder->SetMaxPeriod(1.0);
	this->shooterEncoder->Reset();
	this->shooterEncoder->Start();
	
	this->tiltLowerLimit = new DigitalInput(TILT_LOW_LIMIT_SWITCH_SLOT, TILT_LOW_LIMIT_SWITCH);
	this->tiltUpperLimit = new DigitalInput(TILT_HIGH_LIMIT_SWITCH_SLOT, TILT_HIGH_LIMIT_SWITCH);
	
	this->topLimitSwitch = new DigitalInput(TOP_LIMIT_SWITCH_SLOT, TOP_LIMIT_SWITCH);
	this->botLimitSwitch = new DigitalInput(BOT_LIMIT_SWITCH_SLOT, BOT_LIMIT_SWITCH);
	this->upperLimitSwitch = new DigitalInput(UPPER_LIMIT_SWITCH_SLOT, UPPER_LIMIT_SWITCH);
	this->lowerLimitSwitch = new DigitalInput(LOWER_LIMIT_SWITCH_SLOT, LOWER_LIMIT_SWITCH);
	this->kickerLimitSwitch = new DigitalInput(KICKER_LIMIT_SWITCH_SLOT, KICKER_LIMIT_SWITCH);
	
	printf("SensorSubsystem: constructor completed\n");
}

void SensorSubsystem::Stop()
{
	if (this->leftEncoder != NULL)
		this->leftEncoder->Stop();
	if (this->rightEncoder != NULL)
		this->rightEncoder->Stop();
	if (this->tiltEncoder != NULL)
		this->tiltEncoder->Stop();
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

int SensorSubsystem::GetLeftEncoderValue() {
	return this->leftEncoder->Get();
}

int SensorSubsystem::GetRightEncoderValue() {
	return this->rightEncoder->Get();
}

int SensorSubsystem::GetTiltEncoderValue() {
	return this->tiltEncoder->Get();
}

Encoder *SensorSubsystem::GetTiltEncoder()
{
	return this->tiltEncoder;
}

int SensorSubsystem::GetShooterEncoderValue() {
	return this->shooterEncoder->Get();
}

bool SensorSubsystem::GetTiltLowerLimit() {
	return this->tiltLowerLimit->Get() == 0;
}

bool SensorSubsystem::GetTiltUpperLimit() {
	return this->tiltUpperLimit->Get() == 0;
}

bool SensorSubsystem::GetPizzaTopLimitSwitch()
{
	return this->topLimitSwitch->Get() == 0;
}

bool SensorSubsystem::GetPizzaUpperLimitSwitch()
{
	return this->upperLimitSwitch->Get() == 0;
}

bool SensorSubsystem::GetPizzaLowerLimitSwitch()
{
	return this->lowerLimitSwitch->Get() == 0;
}

bool SensorSubsystem::GetPizzaBottomLimitSwitch()
{
	return this->botLimitSwitch->Get() == 0;
}

bool SensorSubsystem::GetKickerLimitSwitch()
{
	return this->kickerLimitSwitch->Get() == 0;
}
