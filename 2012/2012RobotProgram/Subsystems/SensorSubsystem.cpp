#include "SensorSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/SensorValueDisplayCommand.h"



const float MAXBOTIX_SCALE_FACTOR = (5.0 / 512);



/*
 * A subsytem for holding all of the sensors.  These can be shared and the
 * subsystem doesn't need to be Required by a command to access the sensors, since
 * we're only doing reading here.
 */
SensorSubsystem::SensorSubsystem() : Subsystem("SensorSubsystem") {
	printf("Initializing ball sensor 1\n");
	ballSensor1 = new DigitalInput(BALL_SENSOR_1_CHANNEL);
	
	printf("Initializing ball sensor 2\n");
	ballSensor2 = new DigitalInput(BALL_SENSOR_2_CHANNEL);
	
	printf("Initializing ball sensor 3\n");
	ballSensor3 = new DigitalInput(BALL_SENSOR_3_CHANNEL);
	
	printf("Initializing floor transition sensor\n");
	floorTransitionSensor = new DigitalInput(FLOOR_TRANSITION_SENSOR_CHANNEL);
	
	printf("Initializing arm position sensor\n");
	armPositionSensor = new DigitalInput(ARM_POSITION_SENSOR_CHANNEL);
	armDebounceTimer = NULL;
	
	printf("Initializing yaw gyro\n");
	yawGyro = new Gyro(YAW_GYRO_CHANNEL);
	yawGyro->SetSensitivity(0.007);
	
	printf("Initializing pitch gyro\n");
	pitchGyro = new Gyro(PITCH_GYRO_CHANNEL);
	pitchGyro->SetSensitivity(0.007);
	
	printf("Initializing maxbotics\n");
	maxbotics = new AnalogChannel(MAXBOTICS_CHANNEL);
	
	printf("Sensor initialization complete\n");
}
    
void SensorSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new SensorValueDisplayCommand());
}

bool SensorSubsystem::IsBallPresentSensor1(){
	return ballSensor1->Get() == 0;
}

bool SensorSubsystem::IsBallPresentSensor2(){
	return ballSensor2->Get() == 0;
}

bool SensorSubsystem::IsBallPresentSensor3(){
	return ballSensor3->Get() == 0;
}

bool SensorSubsystem::IsFloorDark() {
	return floorTransitionSensor->Get() == 0;
}

bool SensorSubsystem::IsArmDown() {
	if (armDebounceTimer == NULL){
		armDebounceTimer = new Timer();
		armDebounceTimer->Start();
		lastArmPosition = armPositionSensor->Get();
	}else{
		if(armDebounceTimer->Get() > 0.1){
			armDebounceTimer->Stop();
			armDebounceTimer->Reset();
			armDebounceTimer->Start();
			lastArmPosition = armPositionSensor->Get();
		}
	}
	return lastArmPosition == 0;
}

float SensorSubsystem::GetYawGyroAngle() {
	return yawGyro->GetAngle();
}

float SensorSubsystem::GetPitchGyroAngle() {
	return pitchGyro->GetAngle();
}

float SensorSubsystem::GetRangefinderDistanceInInches() {
	return maxbotics->GetVoltage() / MAXBOTIX_SCALE_FACTOR;
}
