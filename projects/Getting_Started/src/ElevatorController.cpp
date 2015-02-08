/*
 * ElevatorController.cpp
 *
 *   Class to encapsulate the control interface to the elevator apparatus
 *
 */

#include <ElevatorController.h>

ElevatorController::ElevatorController(AnalogInput *vertInput,
										AnalogInput *horizInput,
										SpeedController *vertController1,
										SpeedController *vertController2,
										Relay *horizSpike,
										float vertScaleFactor,
										float horizScaleFactor) {

	this->vertInput = vertInput;
	this->horizInput = horizInput;
	this->vertController1 = vertController1;
	this->vertController2 = vertController2;
	this->horizSpike = horizSpike;
	this->vertScaleFactor = vertScaleFactor;
	this->vertOffset = 0.0;
	this->horizScaleFactor= horizScaleFactor;
	this->horizOffset = -(horizScaleFactor / 2.0);

	vertPot = new AnalogPotentiometer(vertInput, vertScaleFactor, vertOffset);
	horizPot = new AnalogPotentiometer(horizInput, horizScaleFactor, horizOffset);
}

ElevatorController::~ElevatorController(){
	delete vertPot;
	delete horizPot;
}

void ElevatorController::setVertScaleFactor(float scaleFactor){
	vertScaleFactor = scaleFactor;
	delete vertPot;
	vertPot = new AnalogPotentiometer(vertInput, vertScaleFactor, vertOffset);
}

void ElevatorController::setHorizScaleFactor(float scaleFactor){
	horizScaleFactor = scaleFactor;
	delete horizPot;
	horizPot = new AnalogPotentiometer(horizInput, horizScaleFactor, horizOffset);
}

void ElevatorController::resetVertZeroPoint(){
	vertOffset = vertPot->Get();
	delete vertPot;
	vertPot = new AnalogPotentiometer(vertInput, vertScaleFactor, vertOffset);
}

void ElevatorController::resetHorizZeroPoint(){
	horizOffset = horizPot->Get();
	delete horizPot;
	horizPot = new AnalogPotentiometer(horizInput, horizScaleFactor, horizOffset);
}

float ElevatorController::getVertDistance(){
	return vertPot->Get();
}

void ElevatorController::gotoVertDistance(float distance){
	// code to go to the given vertical distance
	float endDistance = distance;
	vertDirection direction = ((endDistance > vertPot->Get()) ? UP : DOWN);
	bool endDistanceReached = false;

	// do not allow endDistance past max or min values
	if((direction == UP) && (endDistance > vertScaleFactor)){
		endDistance = vertScaleFactor;
	}

	if((direction == DOWN) && (endDistance < 0.0)){
		endDistance = 0.0;
	}

	while(!endDistanceReached){
		// control loop to move vertical speed controllers
		float remainingDistance = endDistance - vertPot->Get();

		// this is not synchronizing the motor controls, which
		// appears to require the CAN interface usage
		vertController1->Set(remainingDistance/vertScaleFactor);
		vertController2->Set(remainingDistance/vertScaleFactor);

		if(direction == UP){
			endDistanceReached = vertPot->Get() >= endDistance;
		}
		else{
			endDistanceReached = vertPot->Get() <= endDistance;
		}
	}

	// once the end distance is reached, stop the controllers
	vertController1->Set(0.0);
	vertController2->Set(0.0);
}

void ElevatorController::stepVertDistance(float stepDistance){
	// code to change the vertical distance by the given step
	gotoVertDistance(vertPot->Get() + stepDistance);
}

float ElevatorController::getHorizAngle(){
	return horizPot->Get();
}

void ElevatorController::gotoHorizAngle(float angle){
	// code to go to the given horizontal angle
}

void ElevatorController::stepHorizAngle(float stepAngle){
	// code to change horizontal angle by the given amount
	gotoHorizAngle(horizPot->Get() + stepAngle);
}


