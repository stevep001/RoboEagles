#include "RunCompressorCommand.h"

RunCompressorCommand::RunCompressorCommand() {
	Requires(compressorSubsystem);
}

void RunCompressorCommand::Initialize() {
	compressorSubsystem->Start();
}

void RunCompressorCommand::Execute() {
	
}

bool RunCompressorCommand::IsFinished() {
	return false;
}

//TODO Stop Compressor?
void RunCompressorCommand::End() {
	//compressorSubsystem->Stop();
}

void RunCompressorCommand::Interrupted() {
	//compressorSubsystem->Stop();
}
