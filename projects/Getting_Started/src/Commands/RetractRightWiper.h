#ifndef RetractRightWiper_H
#define RetractRightWiper_H

//#include "../CommandBase.h"
#include "WPILib.h"

class RetractRightWiper: public Command
{
public:
	RetractRightWiper(DoubleSolenoid *doubleSolenoid);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	DoubleSolenoid *doubleSolenoid;
	bool activated;
};



#endif
