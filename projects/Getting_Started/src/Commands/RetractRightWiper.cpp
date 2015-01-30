#include "RetractRightWiper.h"

RetractRightWiper::RetractRightWiper(DoubleSolenoid *doubleSolenoid)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	this->doubleSolenoid = doubleSolenoid;
	activated=false;
}


// Called just before this Command runs the first time
void RetractRightWiper::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void RetractRightWiper::Execute()
{
	printf("RetractRightWiper::Execute(), Button 2 pressed\n");
	doubleSolenoid->Set(DoubleSolenoid::kReverse);
	Wait(0.05);
	doubleSolenoid->Set(DoubleSolenoid::kOff);
	activated=true;
}

// Make this return true when this Command no longer needs to run execute()
bool RetractRightWiper::IsFinished()
{
	return activated;
}

// Called once after isFinished returns true
void RetractRightWiper::End()
{
	activated=false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RetractRightWiper::Interrupted()
{

}
