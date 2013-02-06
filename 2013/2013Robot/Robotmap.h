#ifndef ROBOTMAP_H
#define ROBOTMAP_H

// Digital I/O Sidecar slot 1
#define TOP_LIMIT_SWITCH 1
#define BOT_LIMIT_SWITCH 2
#define UPPER_LIMIT_SWITCH 3
#define LOWER_LIMIT_SWITCH 4
#define FRISBEE_LIMIT_SWITCH 5

// Digital I/O Sidecar slot 2

// Relay Sidecar slot 1

// PWM Sidecar slot 1
#define DRIVE_MOTOR 1
#define DRIVE_MOTOR 2
#define DRIVE_MOTOR 3
#define DRIVE_MOTOR 4
#define PIZZA_BOX_MOTOR 5

// Solinoid slot 1

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

#define PB_TOP_BUTTON 6
#define PB_BOTTOM_BUTTON 7


#endif
