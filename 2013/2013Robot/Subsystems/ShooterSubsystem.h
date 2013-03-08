#ifndef SHOOTERSUBSYSTEM_H
#define SHOOTERSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class ShooterSubsystem: public Subsystem {\
public:
	enum ShooterPower {
		Test,
		Low,
		Normal
	};
private:
	SpeedController *shooterMotor;
	ShooterPower shootingPower;
public:
	ShooterSubsystem();
	void InitDefaultCommand();
	void SetShootingPower(ShooterPower desiredPower);
	ShooterPower ShooterSubsystem::GetShootingPower();
	SpeedController *GetMotor();
};

#endif
