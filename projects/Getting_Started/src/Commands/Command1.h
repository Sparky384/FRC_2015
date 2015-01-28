#ifndef Command1_H
#define Command1_H

//#include "../CommandBase.h"
#include "WPILib.h"

class Command1: public Command
{
public:
	Command1(DoubleSolenoid *doubleSolenoid);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	DoubleSolenoid *doubleSolenoid;
};

#endif
