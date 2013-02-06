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


// Compressor
// Relay (Sidecar) -- Slot 1
//#define UNDERBELT_RELAY_CHANNEL 1
#define COMPRESSOR_RELAY_CHANNEL 2
//#define BELT_RELAY_CHANNEL 3
#define TRAFFIC_COP_RELAY_CHANNEL 4

// Solenoid -- Slot 1
#define THROW_SOLENOID_OUT 1
#define THROW_SOLENOID_IN 2

#define FLAP_SOLENOID_UP 3
#define FLAP_SOLENOID_DOWN 4

#define LIFTER_SOLENOID_UP 6
#define LIFTER_SOLENOID_DOWN 5

// PWM (Sidecar) -- Slot 1
#define DRIVE_MOTOR_L_PWM 1
#define DRIVE_MOTOR_R_PWM 2
#define AIM_MOTOR_PWM 3
#define BELT_MOTOR_PWM 4
#define SWEEPER_MOTOR_PWM 5
#define CAMERA_SERVO_PWM 10


// Digital (sidecar) -- slot 1
#define PRESSURE_SWITCH_CHANNEL 2
#define BALL_SENSOR_1_CHANNEL 3
#define BALL_SENSOR_2_CHANNEL 4 // reserved and unused as of feb 5
#define BALL_SENSOR_3_CHANNEL 5 //   ^
#define	LEFT_BRAKE_CHANNEL 6
#define	RIGHT_BRAKE_CHANNEL 7
#define FLOOR_TRANSITION_SENSOR_CHANNEL 8
#define ARM_POSITION_SENSOR_CHANNEL 9

// Settings for Jaguar coast/brake
#define	JAGUAR_COAST 1
#define JAGUAR_BRAKE 0

// Analog input
#define YAW_GYRO_CHANNEL 1
#define PITCH_GYRO_CHANNEL 2
#define MAXBOTICS_CHANNEL 3
// The analog board is jumpered to feed battery power into slot 8.
// This feeds the driver station power value.
#define BATTERY_POWER_CHANNEL 8

// Joysticks
#define RIGHT_JOYSTICK_PORT 1
#define LEFT_JOYSTICK_PORT 2
#define THROW_JOYSTICK_PORT 3
#define LIFT_JOYSTICK_PORT 4

// THROW_JOYSTICK buttons
#define THROW_TRIGGER_BUTTON 1
#define STOP_BALL_LOADING_BUTTON 7
#define FLAP_TOGGLE_BUTTON 3
#define DECREASE_BUTTON 4
#define INCREASE_BUTTON 5

// Driving Joystick
#define LIFT_DOWN_BUTTON 3
#define LIFT_UP_BUTTON 2

#define RUN_AUTONOMOUS 6
#define RAMP_DRIVE_BUTTON 7
#define DRIVE_FORWARD_TO_TRANSITION_BUTTON 8
#define STOP_AUTONOMOUS_DRIVE 9
#define SELECT_AUTONOMOUS_BUTTON 10

#endif
