#ifndef ROBOTMAP_H
#define ROBOTMAP_H

// Digital I/O Sidecar slot 1
#define TOP_LIMIT_SWITCH_SLOT	1
#define TOP_LIMIT_SWITCH		1
#define BOT_LIMIT_SWITCH_SLOT	1
#define BOT_LIMIT_SWITCH		2
#define UPPER_LIMIT_SWITCH_SLOT	1
#define UPPER_LIMIT_SWITCH		3
#define LOWER_LIMIT_SWITCH_SLOT	1
#define LOWER_LIMIT_SWITCH		4
#define FRISBEE_LIMIT_SWITCH_SLOT	1
#define FRISBEE_LIMIT_SWITCH	5
#define TILT_HIGH_LIMIT_SWITCH_SLOT	1
#define TILT_HIGH_LIMIT_SWITCH	6
#define TILT_LOW_LIMIT_SWITCH_SLOT	1
#define	TILT_LOW_LIMIT_SWITCH	7

// Digital I/O Sidecar slot 2
#define LEFT_GEARBOX_ENCODER_SLOT	2
#define LEFT_GEARBOX_ENCODER_1	1
#define LEFT_GEARBOX_ENCODER_2	2
#define RIGHT_GEARBOX_ENCODER_SLOT	2
#define	RIGHT_GEARBOX_ENCODER_1	3
#define RIGHT_GEARBOX_ENCODER_2	4
#define SHOOTER_WHEEL_ENCODER_SLOT	2
#define SHOOTER_WHEEL_ENCODER_1	5
#define	SHOOTER_WHEEL_ENCODER_2	6
#define TILT_ENCODER_SLOT	2
#define TILT_ENCODER_1			7
#define TILT_ENCODER_2			8
#define	TILT_ENCODER_MAGDEC		9
#define TILT_ENCODER_MAGINC		10

// Relay Sidecar slot 1

// PWM Sidecar slot 1
#define DRIVE_MOTOR_L_1	1
#define DRIVE_MOTOR_R_1	2
#define DRIVE_MOTOR_L_2	3
#define DRIVE_MOTOR_R_2	4
#define PIZZA_BOX_MOTOR	5
#define TILT_MOTOR		6
#define	FRISBEE_EJECT_MOTOR	7

// Solenoid slot 1

// Analog input
#define HORIZONTAL_GYRO_CHANNEL 1
// The analog board is jumpered to feed battery power into slot 8.
// This feeds the driver station power value.
#define BATTERY_POWER_CHANNEL 8

// Settings for Jaguar coast/brake
#define	JAGUAR_COAST 1
#define JAGUAR_BRAKE 0

// Joysticks
#define DRIVE_JOYSTICK_PORT 1
#define TEST_JOYSTICK_PORT 3

// Test Joystick buttons

#define TILT_UP_BUTTON		4
#define TILT_DOWN_BUTTON	5
#define PB_TOP_BUTTON		6
#define PB_BOTTOM_BUTTON	7


#endif
