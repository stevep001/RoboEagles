#ifndef SHOOTERSUBSYSTEM_H
#define SHOOTERSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class ShooterSubsystem: public Subsystem {
private:
	SpeedController *shooterMotor;
	int shootingPower;
public:
	ShooterSubsystem();
	void InitDefaultCommand();
	void SetShootingPower(float power);
	SpeedController *GetMotor();
};

#endif
