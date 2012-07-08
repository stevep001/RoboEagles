#ifndef COMPRESSORSUBSYSTEM_H
#define COMPRESSORSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class CompressorSubsystem: public Subsystem {
private:
	Compressor *compressor;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	CompressorSubsystem();
	void InitDefaultCommand();
	void Start();
};

#endif
