#ifndef COMPRESSORSUBSYSTEM_H
#define COMPRESSORSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author nowireless
 */
class CompressorSubsystem: public Subsystem {
private:
	 Compressor *compressor;
public:
	CompressorSubsystem();
	void InitDefaultCommand();
	void Start();
	void Stop();
};

#endif
