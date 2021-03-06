#include "ExtendRightWiper.h"

ExtendRightWiper::ExtendRightWiper(DoubleSolenoid *doubleSolenoid)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	this->doubleSolenoid = doubleSolenoid;
	activated=false;
}

// Called just before this Command runs the first time
void ExtendRightWiper::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ExtendRightWiper::Execute()
{
	printf("ExtendRightWiper::Execute(), Button 1 pressed\n");
	doubleSolenoid->Set(DoubleSolenoid::kForward);
	Wait(0.05);
	doubleSolenoid->Set(DoubleSolenoid::kOff);
	activated=true;
}

// Make this return true when this Command no longer needs to run execute()
bool ExtendRightWiper::IsFinished()
{
	return activated;
}

// Called once after isFinished returns true
void ExtendRightWiper::End()
{
	activated=false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExtendRightWiper::Interrupted()
{

}
