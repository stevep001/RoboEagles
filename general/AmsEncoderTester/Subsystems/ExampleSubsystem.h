#ifndef EXAMPLE_SUBSYSTEM_H
#define EXAMPLE_SUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class ExampleSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Jaguar *motorController;
	Relay *relay1;
	Encoder *encoder;
	DigitalInput *magDec;
	DigitalInput *magInc;
public:
	ExampleSubsystem();
	void InitDefaultCommand();
	void SetMotorPower(float power);
	int GetCount();
	bool GetMagDec();
	bool GetMagInc();
};

#endif
