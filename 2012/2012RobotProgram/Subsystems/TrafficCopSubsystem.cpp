#include "TrafficCopSubsystem.h"
#include "../Robotmap.h"

TrafficCopSubsystem::TrafficCopSubsystem() : Subsystem("TrafficCopSubsystem") {
	trafficCopRelay = new Relay(TRAFFIC_COP_RELAY_CHANNEL);	
	trafficCopRelay->Set(Relay::kOff);
}
    
void TrafficCopSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}
void TrafficCopSubsystem::ArrowUp(){
	trafficCopRelay->Set(Relay::kForward);
}
void TrafficCopSubsystem::ArrowDown(){
	trafficCopRelay->Set(Relay::kReverse);
}
void TrafficCopSubsystem::Stop(){
	trafficCopRelay->Set(Relay::kOn);
}
void TrafficCopSubsystem::Blank(){
	trafficCopRelay->Set(Relay::kOff);
}
