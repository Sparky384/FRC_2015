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
#define ELEVATOR_VERT_POTENTIOMETER_CHANNEL 2
#define ELEVATOR_HORIZ_POTENTIOMETER_CHANNEL 3

// relay output channels
#define RELAY1_CHANNEL 1

// pneumatic output channels
#define RIGHT_WIPER_SOLENOID_FWD_CHANNEL 0
#define RIGHT_WIPER_SOLENOID_REV_CHANNEL 1

// USB input ports
#define LEFT_JOYSTICK_USB_PORT 1

// digital IO channels
#define FRONT_LEFT_MOTOR_CHANNEL 0
#define REAR_LEFT_MOTOR_CHANNEL 1
#define FRONT_RIGHT_MOTOR_CHANNEL 2
#define REAR_RIGHT_MOTOR_CHANNEL 3




#endif /* ROBOTDEFINITIONS_H_ */
