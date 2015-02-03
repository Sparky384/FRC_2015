#ifndef ElevatorUp_H
#define ElevatorUp_H

//#include "../CommandBase.h"
#include "WPILib.h"

class ElevatorUp: public Command
{
public:
	ElevatorUp( /*SpeedController elevotorMotorA, SpeedController elevatorMotorB */);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();


private:
	//SpeedController motorA;
	//SpeedController motorB;
};

#endif
