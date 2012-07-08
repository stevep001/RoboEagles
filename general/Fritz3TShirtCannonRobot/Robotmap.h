#ifndef ROBOTMAP_H
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


//Joystick
#define JOYSTICK_PORT 1

#define FIRE_BUTTON 1
#define FILL_BUTTON 8

#define UP_BUTTON 3
#define DOWN_BUTTON 2

//Solenoids
#define DOWN_SOLENOID 1
#define UP_SOLENOID 2
#define FILL_SOLENOID 3
#define FIRE_SOLENOID 4

//PWM
#define DRIVE_MOTOR_L_PWM 2
#define DRIVE_MOTOR_R_PWM 1


//Digital i/o
#endif
