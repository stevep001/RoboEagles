#ifndef CAMERACONTROLSUBSYSTEM_H
#define CAMERACONTROLSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author speterson
 */
class CameraControlSubsystem: public Subsystem {
private:
	Servo *cameraServo;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	CameraControlSubsystem();
	void InitDefaultCommand();
	void Move(float pos);
};

#endif
