#include "FrisbeePanSubsystem.h"
#include "../Robotmap.h"

FrisbeePanSubsystem::FrisbeePanSubsystem() : Subsystem("FrisbeePanSubsystem") {
	printf("FrisbeePanSubsystem:: constructor started\n");
	this->panIngestBeltMotor = new Jaguar(PWM_SLOT, PAN_INGEST_BELT_MOTOR);
	this->panLateralBeltMotor = new Jaguar(PWM_SLOT, PAN_LATERAL_BELT_MOTOR);
	printf("FrisbeePanSubsystem: constructor completed.\n");
}
    
void FrisbeePanSubsystem::InitDefaultCommand() {

}
