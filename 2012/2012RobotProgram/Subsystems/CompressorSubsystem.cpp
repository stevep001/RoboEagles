#include "CompressorSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/RunCompressorCommand.h"

CompressorSubsystem::CompressorSubsystem() : Subsystem("CompressorSubsystem") {
	printf("CompressorSubsystem initializing: switch %d relay %d\n", 
			PRESSURE_SWITCH_CHANNEL, COMPRESSOR_RELAY_CHANNEL);
	compressor = new Compressor(PRESSURE_SWITCH_CHANNEL, COMPRESSOR_RELAY_CHANNEL);
}

void CompressorSubsystem::Start() {
	compressor->Start();
}

void CompressorSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new RunCompressorCommand());
}
