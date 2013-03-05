#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include "Commands/Command.h"
#include "Subsystems/FrisbeePanSubsystem.h"
#include "Subsystems/SensorSubsystem.h"
#include "Subsystems/ChassisSubsystem.h"
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
	static FrisbeePanSubsystem* frisbeePanSubsystem;
	static SensorSubsystem* sensorSubsystem;
	static ChassisSubsystem* chassisSubsystem;
	static LcdDisplaySubsystem* lcdDisplaySubsystem;
	static OI *oi;
};

#endif
