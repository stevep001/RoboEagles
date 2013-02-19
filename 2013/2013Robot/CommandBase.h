#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include "Subsystems/PizzaBoxSubsystem.h"
#include "Subsystems/SensorSubsystem.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/ShooterTiltSubsystem.h"
#include "Subsystems/ShooterSubsystem.h"
#include "Subsystems/VisionSubsystem.h"
#include "Subsystems/LEDSubsystem.h"
#include "Subsystems/KickerSubsystem.h"
#include "Subsystems/LcdDisplaySubsystem.h"
#include "OI.h"


/**
 * The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.examplesubsystem
 */
class CommandBase: public Command {
public:
	CommandBase(const char *name);
	CommandBase();
	static void init();
	// Create a single static instance of all of your subsystems
	static PizzaBoxSubsystem *pizzaBoxSubsystem;
	static SensorSubsystem *sensorSubsystem;
	static Chassis *chassis;
	static ShooterTiltSubsystem *shooterTiltSubsystem;
	static ShooterSubsystem *shooterSubsystem;
	static VisionSubsystem *visionSubsystem;
	static LEDSubsystem *ledSubsystem;
	static KickerSubsystem *kickerSubsystem;
	static LcdDisplaySubsystem *lcdDisplaySubsystem;
	static OI *oi;
};

#endif
