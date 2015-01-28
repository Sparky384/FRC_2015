#include "Command1.h"

Command1::Command1(DoubleSolenoid *doubleSolenoid)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	this->doubleSolenoid = doubleSolenoid;
}

// Called just before this Command runs the first time
void Command1::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void Command1::Execute()
{
	printf("Command1::Execute(), Button 1 pressed\n");
	doubleSolenoid->Set(DoubleSolenoid::kForward);
	Wait(0.05);
	doubleSolenoid->Set(DoubleSolenoid::kOff);
}

// Make this return true when this Command no longer needs to run execute()
bool Command1::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void Command1::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Command1::Interrupted()
{

}
