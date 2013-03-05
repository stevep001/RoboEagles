#ifndef ROBOTMAP_Hv 
#define ROBOTMAP_H


/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
 
// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// #define LEFTMOTOR 1
// #define RIGHTMOTOR 2

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// #define RANGE_FINDER_PORT 1
// #define RANGE_FINDER_MODULE 1

#define PWM_SLOT	1

#define DRIVE_MOTOR_L_1	1
#define	DRIVE_MOTOR_R_1	2
#define	PAN_LATERAL_BELT_MOTOR	3	
#define	PAN_INGEST_BELT_MOTOR	4
#define	PAN_LIFT_MOTOR	5

#define	LOADER_FRISBEE_DETECTOR_PORT	4
#define	LOADER_LOW_LIMIT_SWITCH			1
#define PAN_LIFT_ENCODER_1					2
#define	PAN_LIFT_ENCODER_2					3

#define	DRIVER_JOYSTICK			1
#define LOADER_TEST_JOYSTICK	4

#endif
