#include "WPILib.h"
#include "Commands/ExtendRightWiper.h"
#include "Commands/RetractRightWiper.h"

#include "RobotDefinitions.h"

class Robot: public IterativeRobot
{
	Gyro *rateGyro;
	RobotDrive myRobot; // robot drive system

	Joystick stick; // only joystick
	DoubleSolenoid *doubleSolenoid;
	LiveWindow *lw;
	Relay *relay1;

	JoystickButton *button1;
	JoystickButton *button2;

	AnalogInput *elevatorVertPotInput;
	AnalogInput *elevatorHorizPotInput;


	int autoLoopCounter;
	float prevAngle;
	float prevPot;
	float prevLeftEnc;
	float prevRightEnc;
	float autoDistCounter;
	float autoGyroAngle;
	Compressor *compressor;
	Encoder *encLeft;
	Encoder *encRight;

	public:
	Robot() :
		myRobot(FRONT_LEFT_MOTOR_CHANNEL,
				REAR_LEFT_MOTOR_CHANNEL,
				FRONT_RIGHT_MOTOR_CHANNEL,
				REAR_RIGHT_MOTOR_CHANNEL),	// these must be initialized in the same order

		stick(LEFT_JOYSTICK_USB_PORT),		// as they are declared above.
		lw(NULL),
		autoLoopCounter(0)
	{

		myRobot.SetExpiration(0.1);

		compressor = new Compressor();
		rateGyro = new Gyro(GYRO_RATE_INPUT_CHANNEL);
		doubleSolenoid = new DoubleSolenoid(RIGHT_WIPER_SOLENOID_FWD_CHANNEL, RIGHT_WIPER_SOLENOID_REV_CHANNEL);

		encLeft = new Encoder(0,1,false,Encoder::EncodingType::k4X);
		encRight = new Encoder(2,3,true,Encoder::EncodingType::k4X);
		encLeft->SetDistancePerPulse(4.0*3.14159/388.0); // 4" diameter wheel * PI / 360 pulses/rotation
		encRight->SetDistancePerPulse(4.0*3.14159/388.0);
		relay1 = new Relay(1);

		elevatorVertPotInput = AnalogInput(ELEVATOR_VERT_POTENTIOMETER_CHANNEL);
		elevatorHorizPotInput = AnalogInput(ELEVATOR_HORIZ_POTENTIOMETER_CHANNEL);

		//elevatorVertPot = AnalogPotentiometer(new AnalogInput(ELEVATOR_VERT_POTENTIOMETER_CHANNEL));
		//elevatorHorizPot = AnalogPotentiometer(new AnalogInput(ELEVATOR_HORIZ_POTENTIOMETER_CHANNEL));
		//elevatorVertPot->initPot(elevatorVertPotInput, 1.0, 0.0);

		button1 = new JoystickButton(&stick, 1);
		button2 = new JoystickButton(&stick, 2);

		button1->ToggleWhenPressed(new ExtendRightWiper(doubleSolenoid));
		button2->ToggleWhenPressed(new RetractRightWiper(doubleSolenoid));


	}

	private:
	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		printf("Team 812 - It's alive! 2015-02-02\n");
	}

	void AutonomousInit()
	{
		autoLoopCounter = 0;
		autoDistCounter = 0;
		autoGyroAngle = 0;
		encRight->Reset();
		encLeft->Reset();
		rateGyro->Reset();

	}

	void AutonomousPeriodic()
	{
		autoDistCounter = encRight->GetDistance();
		autoGyroAngle = rateGyro->GetAngle();

		if(autoDistCounter < 12.0*4.0*3.14159) // 12 rotations * 4" diameter wheel * PI
		{
		//	printf("Current Distance=%f, gyro angle=%f\n",autoDistCounter,autoGyroAngle );
			printf("%f,%f\n",autoDistCounter,autoGyroAngle );

			myRobot.Drive(-0.3, -autoGyroAngle * 1.2); 	// drive forwards half speed
		}
		else
		{
			myRobot.Drive(0.0, 0.0); 	// stop robot
		}

	}

	void TeleopInit()
	{
		printf("Team 812 - Tally Ho! You're in control.\n");
		encRight->Reset();
		encLeft->Reset();
		rateGyro->Reset();
	}

	void TeleopPeriodic()
	{
		float currAngle;
		float currLeftEnc;
		float currRightEnc;
		float currPot;

		myRobot.ArcadeDrive(stick); // drive with arcade style (use right stick)

		currAngle = rateGyro->GetAngle();
		if( fabs(currAngle - prevAngle) > 0.05) {
			printf("gyro angle = %f, %f, %f\n", currAngle, prevAngle, fabs(currAngle - prevAngle));
			prevAngle = currAngle;
		}

		currPot = elevatorVertPotInput->GetAverageVoltage();

		if(fabs(currPot - prevPot) > 0.01)
		{
			printf("pot reading: %f, %d\n", currPot, elevatorVertPotInput->GetAverageValue());
			prevPot = currPot;
		}

		currLeftEnc = encLeft->GetDistance();
		currRightEnc= encRight->GetDistance();
		if( fabs(currLeftEnc - prevLeftEnc) + fabs(currRightEnc - prevRightEnc) > 0.01) {
			printf("Left Encoder = %f\n", currLeftEnc);
			printf("Right Encoder = %f\n", currRightEnc);
			prevLeftEnc = currLeftEnc;
			prevRightEnc = currRightEnc;
		}

		Scheduler::GetInstance()->Run();

		if(stick.GetRawButton(10)) {
			encLeft->Reset();
			encRight->Reset();
		}
		if(stick.GetRawButton(4)){
			printf("Button 4 pressed\n");
			if (relay1->Get() != Relay::kForward){
				relay1->Set(Relay::kForward);
			} else {
				relay1->Set(Relay::kReverse);

			}
			Wait(0.05);

		}
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
