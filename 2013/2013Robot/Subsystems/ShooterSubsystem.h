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
	Jaguar *shooterJaguar;
public:
	ShooterSubsystem();
	void InitDefaultCommand();
	void SetShootingPower(float power);
};

#endif
