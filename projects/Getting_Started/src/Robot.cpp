#include "WPILib.h"
#include "Commands/ExtendRightWiper.h"
#include "Commands/RetractRightWiper.h"
#include "Utilities.h"

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
	//Command1 *command1;
	JoystickButton *button1;
	JoystickButton *button2;
	AnalogPotentiometer *elevatorPot;

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
	//AnalogInput *rateGyro;
	//AnalogInput *rateGyroTemp;

public:
	Robot() :
			myRobot(0, 1, 2, 3),// these must be initialized in the same order
			elevatorMotorA(5), elevatorMotorB(6), stick(1),	// as they are declared above.
			controlBox(2), lw(NULL), autoLoopCounter(0) {
		myRobot.SetExpiration(0.1);
		//myRobot.SetInvertedMotor(MotorType::)

		// This code enables the USB Microsoft Camera display.
		// You must pick "USB Camera HW" on the Driverstation Dashboard
		// the name of the camera "cam1" can be found in the RoboRio web dashboard
		CameraServer::GetInstance()->SetQuality(90);
		CameraServer::GetInstance()->SetSize(2);
		CameraServer::GetInstance()->StartAutomaticCapture("cam1");

		compressor = new Compressor();
		rateGyro = new Gyro(0);
		dsLeft = new DoubleSolenoid(0, 1);
		dsRight = new DoubleSolenoid(2,3);
		//rateGyro = new AnalogInput(0);
		//rateGyroTemp = new AnalogInput(1);
		encLeft = new Encoder(0, 1, false, Encoder::EncodingType::k4X);
		encRight = new Encoder(2, 3, true, Encoder::EncodingType::k4X);
		encLeft->SetDistancePerPulse(4.0 * 3.14159 / 388.0); // 4" diameter wheel * PI / 360 pulses/rotation
		encRight->SetDistancePerPulse(4.0 * 3.14159 / 388.0);
		relay1 = new Relay(1);
//		elevatorPot = new AnalogInput(2);
		elevatorPot = new AnalogPotentiometer(2);

		//command1 = new Command1(doubleSolenoid);
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

		//printf("Hello 812!");

	}

	void AutonomousPeriodic() {
		double robotDriveCurve;
		autoDistCounter = encRight->GetDistance();
		autoGyroAngle = rateGyro->GetAngle();
		robotDriveCurve = PwmLimit(-autoGyroAngle * 1.2);

		if (autoDistCounter <= autoMaxDistance)
				{
			//	printf("Current Distance=%f, gyro angle=%f\n",autoDistCounter,autoGyroAngle );
			printf("Distance: %f, Turn direction: %f, Direction error: %f, Goal: %f\n", autoDistCounter, robotDriveCurve, autoGyroAngle, autoMaxDistance);

			myRobot.Drive(-0.3, robotDriveCurve); // drive forwards half speed
		} else {
			myRobot.Drive(0.0, 0.0); 	// stop robot
		}

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
		//rateGyro->GetVoltage();
		//rateGyroTemp->GetVoltage();
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
		/*	if( stick.GetRawButton(1)) {
		 printf("Button 1 pressed\n");
		 doubleSolenoid->Set(DoubleSolenoid::kForward);
		 Wait(0.05);
		 doubleSolenoid->Set(DoubleSolenoid::kOff);
		 } else */
		/*	if(stick.GetRawButton(2)) {
		 printf("Button 2 pressed\n");
		 doubleSolenoid->Set(DoubleSolenoid::kReverse);
		 Wait(0.05);
		 doubleSolenoid->Set(DoubleSolenoid::kOff);
		 }  */
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
