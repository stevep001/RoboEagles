#ifndef ROBOTMAP_H
#define ROBOTMAP_H

// Digital I/O Sidecar slot 1
#define LEFT_GEARBOX_ENCODER_SLOT	1
#define LEFT_GEARBOX_ENCODER_1	1
#define LEFT_GEARBOX_ENCODER_2	2

#define RIGHT_GEARBOX_ENCODER_SLOT	1
#define	RIGHT_GEARBOX_ENCODER_1	3
#define RIGHT_GEARBOX_ENCODER_2	4

#define TILT_ENCODER_SLOT	1
#define TILT_ENCODER_1			5
#define TILT_ENCODER_2			6
#define TILT_ENCODER_MAGINC		7
#define	TILT_ENCODER_MAGDEC		8

#define SHOOTER_WHEEL_ENCODER_SLOT	1
#define SHOOTER_WHEEL_ENCODER_1	9
#define	SHOOTER_WHEEL_ENCODER_2	10


// Digital I/O Sidecar slot 2
#define TILT_HIGH_LIMIT_SWITCH_SLOT	2
#define TILT_HIGH_LIMIT_SWITCH	1

#define TOP_LIMIT_SWITCH_SLOT	2
#define TOP_LIMIT_SWITCH		2

#define BOT_LIMIT_SWITCH_SLOT	2
#define BOT_LIMIT_SWITCH		3

#define UPPER_LIMIT_SWITCH_SLOT	2
#define UPPER_LIMIT_SWITCH		4

#define LOWER_LIMIT_SWITCH_SLOT	2
#define LOWER_LIMIT_SWITCH		5

#define FRISBEE_LIMIT_SWITCH_SLOT	2
#define FRISBEE_LIMIT_SWITCH	6

#define KICKER_LIMIT_SWITCH_SLOT	2
#define KICKER_LIMIT_SWITCH	7

#define TILT_LOW_LIMIT_SWITCH_SLOT	2
#define	TILT_LOW_LIMIT_SWITCH	8

// Relay Sidecar slot 1

// PWM Sidecar slot 1
#define PWM_SLOT		1
// Chassis does not obey the PWM_SLOT as there isn't a 4 arg constructor that accepts the slot.

#define DRIVE_MOTOR_L_1			1
#define DRIVE_MOTOR_R_1			2
#define PAN_LIFT_MOTOR			3
#define PAN_INGEST_BELT_MOTOR	4
#define	PAN_LATERAL_BELT_MOTOR	5
#define TILT_MOTOR				6
#define PIZZA_BOX_MOTOR			7
#define	KICKER_MOTOR		8
#define SHOOTER_MOTOR			9



// Solenoid slot 1
#define	BLUE_LED_STRIP		1
#define	YELLOW_LED_STRIP	2
#define	GREEN_RING			3

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

#define	RUN_SHOOTER_BUTTON	1
#define	TEST_KICKER_BUTTON	2
#define	SHOOTER_TILT_45_BUTTON	3
#define PB_TOP_BUTTON		6
#define PB_BOTTOM_BUTTON	7
#define	TEST_VISION_BUTTON	8

#define TILT_UP_COMMANDED_BUTTON	11
#define	TILT_DOWN_COMMANDED_BUTTON	10

#endif
