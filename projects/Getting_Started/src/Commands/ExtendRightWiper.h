#ifndef ExtendRightWiper_H
#define ExtendRightWiper_H

//#include "../CommandBase.h"
#include "WPILib.h"

class ExtendRightWiper: public Command
{
public:
	ExtendRightWiper(DoubleSolenoid *doubleSolenoid);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	DoubleSolenoid *doubleSolenoid;
};


#endif
