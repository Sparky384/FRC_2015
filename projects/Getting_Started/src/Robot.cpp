#include "WPILib.h"
#include "Commands/ExtendRightWiper.h"
#include "Commands/RetractRightWiper.h"
#include "Utilities.h"

#include "RobotDefinitions.h"

class Robot: public IterativeRobot {
	Gyro *rateGyro;
	RobotDrive myRobot; // robot drive system
	Jaguar elevatorMotorA;
	Jaguar elevatorMotorB;
	Joystick stick; // only joystick
	Joystick controlBox;
	DoubleSolenoid *dsLeft;
	DoubleSolenoid *dsRight;

	LiveWindow *lw;
	Relay *relay1;

	JoystickButton *button1;
	JoystickButton *button2;
	AnalogPotentiometer *elevatorPot;
	AnalogInput *elevatorVertPotInput;
	AnalogInput *elevatorHorizPotInput;


	int autoLoopCounter;
	float prevAngle;
	float prevPot;
	float prevLeftEnc;
	float prevRightEnc;
	float autoDistCounter;
	float autoMaxDistance;
	float autoGyroAngle;
	bool b[7];
	int wiperState = 0;

	Compressor *compressor;
	Encoder *encLeft;
	Encoder *encRight;

public:
	Robot() :
		myRobot(FRONT_LEFT_MOTOR_CHANNEL,
				REAR_LEFT_MOTOR_CHANNEL,
				FRONT_RIGHT_MOTOR_CHANNEL,
				REAR_RIGHT_MOTOR_CHANNEL),	// these must be initialized in the same order
											// as they are declared above.
		elevatorMotorA(ELEVATOR_MOTOR_CHANNEL_A),
		elevatorMotorB(ELEVATOR_MOTOR_CHANNEL_B),
		stick(LEFT_JOYSTICK_USB_PORT),
		controlBox(CONTROL_BOX_USB_PORT),
		lw(NULL),
		autoLoopCounter(0)
		{

		myRobot.SetExpiration(0.1);
		//myRobot.SetInvertedMotor(MotorType::)

		// This code enables the USB Microsoft Camera display.
		// You must pick "USB Camera HW" on the Driverstation Dashboard
		// the name of the camera "cam1" can be found in the RoboRio web dashboard
		CameraServer::GetInstance()->SetQuality(90);
		CameraServer::GetInstance()->SetSize(2);
		CameraServer::GetInstance()->StartAutomaticCapture("cam1");

		compressor = new Compressor();
		rateGyro = new Gyro(GYRO_RATE_INPUT_CHANNEL);
		dsLeft = new DoubleSolenoid(LEFT_WIPER_SOLENOID_FWD_CHANNEL, LEFT_WIPER_SOLENOID_REV_CHANNEL);
		dsRight = new DoubleSolenoid(RIGHT_WIPER_SOLENOID_FWD_CHANNEL, RIGHT_WIPER_SOLENOID_REV_CHANNEL);
		encLeft = new Encoder(LEFT_WHEEL_ENCODER_CHANNEL_A, LEFT_WHEEL_ENCODER_CHANNEL_B,
								false, Encoder::EncodingType::k4X);
		encRight = new Encoder(RIGHT_WHEEL_ENCODER_CHANNEL_A, RIGHT_WHEEL_ENCODER_CHANNEL_B,
								true, Encoder::EncodingType::k4X);
		encLeft->SetDistancePerPulse(4.0 * 3.14159 / 388.0); // 4" diameter wheel * PI / 360 pulses/rotation
		encRight->SetDistancePerPulse(4.0 * 3.14159 / 388.0);
		relay1 = new Relay(1);

		elevatorVertPotInput = new AnalogInput(ELEVATOR_VERT_INPUT_CHANNEL);
		elevatorHorizPotInput = new AnalogInput(ELEVATOR_HORIZ_INPUT_CHANNEL);

		button1 = new JoystickButton(&stick, 1);
		button2 = new JoystickButton(&stick, 2);

		//button1->ToggleWhenPressed(new ExtendRightWiper(doubleSolenoid));
		//button2->ToggleWhenPressed(new RetractRightWiper(doubleSolenoid));
	}

private:
	void RobotInit() {
		lw = LiveWindow::GetInstance();
		printf("Team 812 - It's alive! 2015-02-02\n");
	}
	void DisabledInit() {
		printf("Team 812 - DisabledInit\n");
	}
	void DisabledPeriodic() {
		//printf("Team 812 - DisabledPeriodic\n");
	}

	void AutonomousInit() {
		autoLoopCounter = 0;
		autoDistCounter = 0;
		autoMaxDistance = 12.0 * 4.0 * 3.14159;  // 12 rotations * 4" diameter wheel * PI
		autoGyroAngle = 0;
		encRight->Reset();
		encLeft->Reset();
		rateGyro->Reset();

		for (int i = 1; i <= 7; i++) {
			b[i] = controlBox.GetRawButton(i);
			printf("button[%d] = %s\n", i, b[i] ? "true":"false");
		}

		//printf("Hello 812!");

	}

	void AutonomousPeriodic() {
		double robotDriveCurve;
		if(autoLoopCounter++ < 1000) {
			if(!b[4]) {
				autoDistCounter = encRight->GetDistance();
				autoGyroAngle = rateGyro->GetAngle();
				robotDriveCurve = PwmLimit(-autoGyroAngle * 1.2);

				if (-autoDistCounter <= 24.0 )
				{
					printf("Distance: %f, Turn direction: %f, Direction error: %f, Goal: %f\n", autoDistCounter, robotDriveCurve, autoGyroAngle, autoMaxDistance);

					myRobot.Drive(0.35, robotDriveCurve); // drive forwards half speed
					Wait(0.02);
				} else {
					if (autoGyroAngle > -90.0) {
						printf("Try turning left\n");
						myRobot.Drive(0.1, -1.0);
					} else {
						myRobot.Drive(0.0, 0.0); 	// stop robot
						printf("Robot stopped\n");
					}
				}
			} else {
				printf("Autonomous mode is OFF\n");
				Wait(3.0);
			}
		}
		myRobot.Drive(0.0, 0.0);
	}

	void TeleopInit() {
		printf("Team 812 - Tally Ho! You're in control.\n");
		encRight->Reset();
		encLeft->Reset();
		rateGyro->Reset();
	}

	void TeleopPeriodic() {
		float currAngle;
		float currLeftEnc;
		float currRightEnc;
		float currPot;

		myRobot.ArcadeDrive(stick); // drive with arcade style (use right stick)

		currAngle = rateGyro->GetAngle();
		if (fabs(currAngle - prevAngle) > 0.10) {
			printf("gyro angle = %f, %f, %f\n", currAngle, prevAngle,
					fabs(currAngle - prevAngle));
			prevAngle = currAngle;
		}
		currPot = elevatorPot->Get();
		if (fabs(currPot - prevPot) > 0.01) {
			printf("pot reading: %f\n", currPot);
			prevPot = currPot;
		}

		currLeftEnc = encLeft->GetDistance();
		currRightEnc = encRight->GetDistance();
		if (fabs(currLeftEnc - prevLeftEnc) + fabs(currRightEnc - prevRightEnc)
				> 0.01) {
			printf("Left Encoder = %f\n", currLeftEnc);
			printf("Right Encoder = %f\n", currRightEnc);
			prevLeftEnc = currLeftEnc;
			prevRightEnc = currRightEnc;
		}

		Scheduler::GetInstance()->Run();

		for (int i = 1; i <= 7; i++) {
			b[i] = controlBox.GetRawButton(i);
		}

		if (b[1] == 0 && b[2] == 1 && wiperState != 1) {
			printf("Tail off\n");
			wiperState = 1;
			// Pistons should be contracted. Wedge should be closed
			//Retract left piston.
			dsLeft->Set(DoubleSolenoid::kReverse);
			Wait(.2);
			dsLeft->Set(DoubleSolenoid::kOff);
			//Retract right piston
			dsRight->Set(DoubleSolenoid::kReverse);
			Wait(.2);
			dsRight->Set(DoubleSolenoid::kOff);

		} else if (b[1] == 0 && b[2] == 0 && wiperState != 2) {
			printf("Tail Rev\n");
			wiperState = 2;
			//Left side wedge should be open. Left piston extended and right piston contracted
			//Extend left piston
			dsLeft->Set(DoubleSolenoid::kForward);
			Wait(.2);
			dsLeft->Set(DoubleSolenoid::kOff);
			//Retract right piston
			dsRight->Set(DoubleSolenoid::kReverse);
			Wait(.2);
			dsRight->Set(DoubleSolenoid::kOff);
		} else if (b[1] == 1 && b[2] == 1 && wiperState != 3) {
			printf("Tail Fwd\n");
			wiperState = 3;
			//Right side wedge should be open. Right piston extended and left piston contracted.
			//Extend right piston
			dsRight->Set(DoubleSolenoid::kForward);
			Wait(.2);
			dsRight->Set(DoubleSolenoid::kOff);
			//Retract left piston
			dsLeft->Set(DoubleSolenoid::kReverse);
			Wait(.2);
			dsLeft->Set(DoubleSolenoid::kOff);
		} else if (b[1] && !b[2]) {
			printf("Uh oh Button problem!\n");
			wiperState = 0;
		}
		if (stick.GetRawButton(10)) {
			encLeft->Reset();
			encRight->Reset();
		}
		if (stick.GetRawButton(4)) {
			printf("Button 4 pressed\n");
			if (relay1->Get() != Relay::kForward) {
				relay1->Set(Relay::kForward);
			} else {
				relay1->Set(Relay::kReverse);

			}
			Wait(0.05);

		}
	}

	void TestPeriodic() {
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
