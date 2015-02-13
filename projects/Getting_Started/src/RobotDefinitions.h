/*
 * RobotDefinitions.h
 *
 *  File to hold robot definitions.  E.g. intput channels, etc.
 *
 */

#ifndef ROBOTDEFINITIONS_H_
#define ROBOTDEFINITIONS_H_

// location of configuration file with key/value pairs
#define CONFIG_FILE_LOCATION "/home/lvuser/config.txt" // use this path when deploying to the robot

// analog input channels
#define GYRO_RATE_INPUT_CHANNEL 0
#define GYRO_TEMP_INPUT_CHANNEL 1
#define ELEVATOR_VERT_INPUT_CHANNEL 2
#define ELEVATOR_HORIZ_INPUT_CHANNEL 3

// pneumatic output channels
#define LEFT_WIPER_SOLENOID_FWD_CHANNEL 0
#define LEFT_WIPER_SOLENOID_REV_CHANNEL 1
#define RIGHT_WIPER_SOLENOID_FWD_CHANNEL 2
#define RIGHT_WIPER_SOLENOID_REV_CHANNEL 3

// USB input ports
#define LEFT_JOYSTICK_USB_PORT 1
#define RIGHT_JOYSTICK_USB_PORT 0
#define CONTROL_BOX_USB_PORT 2

// PWM digital IO channels
#define FRONT_LEFT_MOTOR_CHANNEL 0
#define REAR_LEFT_MOTOR_CHANNEL 1
#define FRONT_RIGHT_MOTOR_CHANNEL 2
#define REAR_RIGHT_MOTOR_CHANNEL 3
#define ELEVATOR_MOTOR_CHANNEL_A 4
#define ELEVATOR_MOTOR_CHANNEL_B 5
#define SWING_ARM_MOTOR_CHANNEL 6

// DIO channels
#define LEFT_WHEEL_ENCODER_CHANNEL_A 2  //Diego- I switched the channels for the left and right
#define LEFT_WHEEL_ENCODER_CHANNEL_B 3
#define RIGHT_WHEEL_ENCODER_CHANNEL_A 0
#define RIGHT_WHEEL_ENCODER_CHANNEL_B 1

// RELAY channels
#define LEFT_INTAKE_WHEEL_CHANNEL 1
#define RIGHT_INTAKE_WHEEL_CHANNEL 0

#endif /* ROBOTDEFINITIONS_H_ */
