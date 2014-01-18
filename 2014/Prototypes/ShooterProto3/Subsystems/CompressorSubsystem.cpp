#include "CompressorSubsystem.h"
#include "../Commands/RunCompressorCommand.h"
#include "../Robotmap.h"

CompressorSubsystem::CompressorSubsystem() : Subsystem("CompressorSubsystem") {
	 printf("CompressorSubsystem initializing: switch %d relay %d\n", 
	                        PRESSURE_SWITCH_CHANNEL, COMPRESSOR_RELAY_CHANNEL);
	        compressor = new Compressor(PRESSURE_SWITCH_CHANNEL, COMPRESSOR_RELAY_CHANNEL);
}
    
void CompressorSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new RunCompressorCommand());
}

void CompressorSubsystem::Start() {
	printf("Starting Compressor\n");
	this->compressor->Start();
}

void CompressorSubsystem::Stop() {
	//this->compressor->Stop();
}
