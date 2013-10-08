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
	printf("1");
	this->tiltEncoderMagDec = new DigitalInput(TILT_ENCODER_SLOT, TILT_ENCODER_MAGDEC);
	this->tiltEncoderMagInc = new DigitalInput(TILT_ENCODER_SLOT, TILT_ENCODER_MAGINC);
	
	this->leftEncoder = new Encoder(LEFT_GEARBOX_ENCODER_1, LEFT_GEARBOX_ENCODER_2, false, CounterBase::k4X);
	this->leftEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->leftEncoder->SetDistancePerPulse(1);
	this->leftEncoder->SetMaxPeriod(1.0);
	this->leftEncoder->Reset();
	this->leftEncoder->Start();
	printf("2");
	
	this->rightEncoder = new Encoder(RIGHT_GEARBOX_ENCODER_1, RIGHT_GEARBOX_ENCODER_2, false, CounterBase::k4X);
	this->rightEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->rightEncoder->SetDistancePerPulse(1);
	this->rightEncoder->SetMaxPeriod(1.0);
	this->rightEncoder->Reset();
	this->rightEncoder->Start();
	printf("3");

/*	this->tiltEncoder = new Encoder(TILT_ENCODER_SLOT, TILT_ENCODER_1, TILT_ENCODER_SLOT, TILT_ENCODER_2, 
			true, CounterBase::k4X);
	this->tiltEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->tiltEncoder->SetDistancePerPulse(1);
	this->tiltEncoder->SetMaxPeriod(1.0);
	this->tiltEncoder->Reset();
	this->tiltEncoder->Start(); */
	printf("4");

	this->shooterEncoder1 = new Encoder(SHOOTER_WHEEL_ENCODER_1_SLOT, SHOOTER_WHEEL_ENCODER_1_PORT_1, 
			SHOOTER_WHEEL_ENCODER_1_SLOT, SHOOTER_WHEEL_ENCODER_1_PORT_2, false, CounterBase::k1X);
	this->shooterEncoder1->SetPIDSourceParameter(Encoder::kDistance);
	this->shooterEncoder1->SetDistancePerPulse(1);
	this->shooterEncoder1->SetMaxPeriod(1.0);
	this->shooterEncoder1->Reset();
	this->shooterEncoder1->Start();
	printf("5");

//	this->shooterEncoder2 = new Encoder(SHOOTER_WHEEL_ENCODER_2_SLOT, SHOOTER_WHEEL_ENCODER_2_PORT_1, 
//			false, CounterBase::k1X);
//	this->shooterEncoder2->SetPIDSourceParameter(Encoder::kDistance);
//	this->shooterEncoder2->SetDistancePerPulse(1);
//	this->shooterEncoder2->SetMaxPeriod(1.0);
//	this->shooterEncoder2->Reset();
//	this->shooterEncoder2->Start();
	printf("6");

	this->tiltLowerLimit = new DigitalInput(TILT_LOW_LIMIT_SWITCH_SLOT, TILT_LOW_LIMIT_SWITCH);
	this->tiltUpperLimit = new DigitalInput(TILT_HIGH_LIMIT_SWITCH_SLOT, TILT_HIGH_LIMIT_SWITCH);
	printf("7");

	this->topLimitSwitch = new DigitalInput(TOP_LIMIT_SWITCH_SLOT, TOP_LIMIT_SWITCH);
	this->botLimitSwitch = new DigitalInput(BOT_LIMIT_SWITCH_SLOT, BOT_LIMIT_SWITCH);
	this->upperLimitSwitch = new DigitalInput(UPPER_LIMIT_SWITCH_SLOT, UPPER_LIMIT_SWITCH);
	this->lowerLimitSwitch = new DigitalInput(LOWER_LIMIT_SWITCH_SLOT, LOWER_LIMIT_SWITCH);
	this->kickerLimitSwitch = new DigitalInput(KICKER_LIMIT_SWITCH_SLOT, KICKER_LIMIT_SWITCH);
	this->frisbeeInBoxSwitch = new DigitalInput(FRISBEE_LIMIT_SWITCH_SLOT, FRISBEE_LIMIT_SWITCH);
	
	this->loaderFrisbeeDetector = new DigitalInput(LOADER_FRISBEE_DETECTOR_SLOT, LOADER_FRISBEE_DETECTOR_PORT);
	this->loaderLowLimitSwitch = new DigitalInput(LOADER_LOW_LIMIT_SWITCH_SLOT, LOADER_LOW_LIMIT_SWITCH_PORT);
	printf("8");

	this->panLiftEncoder = new Encoder(PAN_LIFT_ENCODER_1, PAN_LIFT_ENCODER_2, false, CounterBase::k4X);
	printf("9");

	this->panLiftEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->panLiftEncoder->SetDistancePerPulse(1);
	this->panLiftEncoder->SetMaxPeriod(1.0);
	this->panLiftEncoder->Reset();
	this->panLiftEncoder->Start();
	
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
	//return this->tiltEncoder->Get();
	return 0;
}

//Encoder *SensorSubsystem::GetTiltEncoder()
//{
//	return this->tiltEncoder;
//}

int SensorSubsystem::GetShooterEncoder1Value() {
	return this->shooterEncoder1->Get();
}

//int SensorSubsystem::GetShooterEncoder2Value() {
//	return this->shooterEncoder2->Get();
//}

bool SensorSubsystem::GetTiltLowerLimit() {
	return this->tiltLowerLimit->Get() == 0;
}

bool SensorSubsystem::GetTiltUpperLimit() {
	return this->tiltUpperLimit->Get() == 0;
}

bool SensorSubsystem::IsFrisbeeInBox()
{
	return this->frisbeeInBoxSwitch->Get() == 0;
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

bool SensorSubsystem::IsKickerStowed()
{
	return this->kickerLimitSwitch->Get() == 0;
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

Gyro* SensorSubsystem::GetHorizontalGyro() {
	return this->horizontalGyro;
}

Encoder *SensorSubsystem::GetLeftDriveEncoder() {
	return this->leftEncoder;
}

Encoder *SensorSubsystem::GetRightDriveEncoder() {
	return this->rightEncoder;
}
