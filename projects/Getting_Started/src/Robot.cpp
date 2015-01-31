#include "WPILib.h"
#include "Commands/ExtendRightWiper.h"
#include "Commands/RetractRightWiper.h"

class Robot: public IterativeRobot
{
	Gyro *rateGyro;
	RobotDrive myRobot; // robot drive system
	Joystick stick; // only joystick
	DoubleSolenoid *doubleSolenoid;
	LiveWindow *lw;
	Relay *relay1;
	//Command1 *command1;
	JoystickButton *button1;
	JoystickButton *button2;

	int autoLoopCounter;
	float prevAngle;
	float prevLeftEnc;
	float prevRightEnc;
	Compressor *compressor;
	Encoder *encLeft;
	Encoder *encRight;
	//AnalogInput *rateGyro;
	//AnalogInput *rateGyroTemp;

	public:
	Robot() :
		myRobot(0, 1, 2, 3),	// these must be initialized in the same order
		stick(1),		// as they are declared above.
		lw(NULL),
		autoLoopCounter(0)
	{
		myRobot.SetExpiration(0.1);
		//myRobot.SetInvertedMotor(MotorType::)
		compressor = new Compressor();
		rateGyro = new Gyro(0);
		doubleSolenoid = new DoubleSolenoid(0,1);
		//rateGyro = new AnalogInput(0);
		//rateGyroTemp = new AnalogInput(1);
		encLeft = new Encoder(0,1,false,Encoder::EncodingType::k4X);
		encRight = new Encoder(2,3,true,Encoder::EncodingType::k4X);
		encLeft->SetDistancePerPulse(0.03488);
		encRight->SetDistancePerPulse(0.03488);
		relay1 = new Relay(1);
		//command1 = new Command1(doubleSolenoid);
		button1 = new JoystickButton(&stick, 1);
		button2 = new JoystickButton(&stick, 2);

		button1->ToggleWhenPressed(new ExtendRightWiper(doubleSolenoid));
		button2->ToggleWhenPressed(new RetractRightWiper(doubleSolenoid));

	}

	private:
	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
		printf("Team 812 - It's alive!\n");
	}

	void AutonomousInit()
	{
		autoLoopCounter = 0;
		encRight->Reset();
		//printf("Hello 812!");


	}

	void AutonomousPeriodic()
	{
		if(encRight->GetDistance() < 12.5 * 4.) //Check if we've completed 100 loops (approximately 2 seconds)
		{
			myRobot.Drive(-0.2, 0.0); 	// drive forwards half speed
			autoLoopCounter++;
			printf("Current Distance=%f\n",encRight->GetDistance() );
		}
		else
		{
			myRobot.Drive(0.0, 0.0); 	// stop robot
		}

	}

	void TeleopInit()
	{
		printf("Team 812 - Tally Ho! You're in control.\n");
	}

	void TeleopPeriodic()
	{
		float currAngle;
		float currLeftEnc;
		float currRightEnc;

		myRobot.ArcadeDrive(stick); // drive with arcade style (use right stick)
		//rateGyro->GetVoltage();
		//rateGyroTemp->GetVoltage();
		currAngle = rateGyro->GetAngle();
		if( fabs(currAngle - prevAngle) > 0.01) {
			printf("gyro angle = %f, %f, %f\n", currAngle, prevAngle, fabs(currAngle - prevAngle));
		}
		prevAngle = currAngle;
		currLeftEnc = encLeft->GetDistance();
		currRightEnc= encRight->GetDistance();
		if( fabs(currLeftEnc - prevLeftEnc) + fabs(currRightEnc - prevRightEnc) > 0.01) {
			printf("Left Encoder = %f\n", currLeftEnc);
			printf("Right Encoder = %f\n", currRightEnc);
		}

		prevLeftEnc = currLeftEnc;
		prevRightEnc = currRightEnc;

		Scheduler::GetInstance()->Run();

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
