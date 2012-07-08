#ifndef BALLLOADERSUBSYSTEM_H
#define BALLLOADERSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class BallLoaderSubsystem: public Subsystem {
private:
	Solenoid *flapSolenoidDown;
	Solenoid *flapSolenoidUp;
//	Relay *beltRelay;
//	Relay *underBeltRelay;
	Jaguar *beltJag;
	Jaguar *sweeperJag;
	
	DigitalInput *ballSensor1;

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	BallLoaderSubsystem();
	void InitDefaultCommand();	
	void BallLoaderSubsystem::BeltUp();
	void BallLoaderSubsystem::BeltDown();
	void BallLoaderSubsystem::BeltOff();
	void BallLoaderSubsystem::FlapUp();
	void BallLoaderSubsystem::FlapDown();
};

#endif
