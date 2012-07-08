#ifndef TRAFFICCOPSUBSYSTEM_H
#define TRAFFICCOPSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class TrafficCopSubsystem: public Subsystem {
private:
	Relay * trafficCopRelay;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	TrafficCopSubsystem();
	void InitDefaultCommand();
	void ArrowUp();
	void ArrowDown();
	void Stop();
	void Blank();
};

#endif
