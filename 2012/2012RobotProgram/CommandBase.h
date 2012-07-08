#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include "Commands/Command.h"
#include "Subsystems/Chassis.h"
#include "OI.h"
#include "Subsystems/CompressorSubsystem.h"
#include "Subsystems/ThrowerSubsystem.h"
#include "Subsystems/BallLoaderSubsystem.h"
#include "Subsystems/LifterSubsystem.h"
#include "Subsystems/SensorSubsystem.h"
#include "Subsystems/TrafficCopSubsystem.h"
#include "Subsystems/LCDSubsystem.h"
#include "Subsystems/CameraControlSubsystem.h"

#define MIN_THROWING_POWER 2
#define MAX_THROWING_POWER 40

#define MIN_AUTONOMOUS_MODE 1

#define ABRT_IMMEDIATE_MODE 1
#define ABRT_2SEC_MODE 2
#define ABRT_4SEC_MODE 3
#define ABRT_6SEC_MODE 4
#define ABRT_8SEC_MODE 5
#define ABRM_IMMEDIATE_MODE 6
#define ABRM_2SEC_MODE 7
#define ABRM_4SEC_MODE 8
#define ABRM_6SEC_MODE 9
#define ABRM_8SEC_MODE 10
#define ABLM_IMMEDIATE_MODE 11
#define ABLM_2SEC_MODE 12
#define ABLM_4SEC_MODE 13
#define ABLM_6SEC_MODE 14
#define ABLM_8SEC_MODE 15

#define AUTO_RAMP_BASKETS_MODE 16
#define AUTO_DO_NOTHING_MODE 17

//ANGLE TESTING CODE
#define ABRT_160_TEST 18
#define ABRT_170_TEST 19
#define ABRT_180_TEST 20
#define ABRT_190_TEST 21
#define ABRM_200_TEST 22
#define ABRM_210_TEST 23
#define ABRM_220_TEST 24
#define ABRM_230_TEST 25

#define BALL_EJECT_MODE 26

#define MAX_AUTONOMOUS_MODE 26

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
	static Chassis *chassis;
	static CompressorSubsystem *compressorSubsystem;
	static OI *oi;
	static ThrowerSubsystem *throwerSubsystem;
	static BallLoaderSubsystem *ballLoaderSubsystem;
	static LifterSubsystem *lifterSubsystem;
	static SensorSubsystem *sensorSubsystem;
	static	TrafficCopSubsystem *trafficCopSubsystem;
	static LCDSubsystem *lcdSubsystem;
	static CameraControlSubsystem *cameraControlSubsystem;
	static int throwerPower;
	static bool flapDown;
	static int autonomousProgram;
};

#endif
