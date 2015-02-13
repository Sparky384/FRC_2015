/*
 * ElevatorController.h
 *
 *  Class to encapsulate the control interface to the elevator apparatus
 *
 */

#ifndef SRC_ELEVATORCONTROLLER_H_
#define SRC_ELEVATORCONTROLLER_H_

#include "WPILib.h"
#include <atomic>

using std::atomic;

// for control logic use
enum vertDirection{UP=0,
					DOWN=1};

enum horizDirection{INCREASING=0,
					DECREASING=1};

class ElevatorController {
public:
	ElevatorController(AnalogInput *vertInput, AnalogInput *horizInput,
						SpeedController *vertController1, SpeedController *vertController2,
						Relay *horizSpike, float vertScaleFactor=1.0, float horizScaleFactor=1.0);

	virtual ~ElevatorController();

	void setVertScaleFactor(float scaleFactor);
	void setHorizScaleFactor(float scaleFactor);
	void resetVertZeroPoint();
	void resetHorizZeroPoint();
	float getVertDistance();
	void gotoVertDistance(float distance);
	void stepVertDistance(float stepDistance);
	float getHorizAngle();
	void gotoHorizAngle(float angle);
	void stepHorizAngle(float stepAngle);
	void run();
	void halt();

private:
	AnalogInput *vertInput;
	AnalogInput *horizInput;
	AnalogPotentiometer *vertPot;
	AnalogPotentiometer *horizPot;
	SpeedController *vertController1;
	SpeedController *vertController2;
	Relay *horizSpike;
	float vertScaleFactor;
	float vertOffset;
	float horizScaleFactor; // the full angle the horizontal arm can sweep through, e.g. -25deg to 25deg = scaleFactor of 50
	float horizOffset;

	// use atomic variables here to avoid possible threading issues
	atomic<float> targetDistance;
	atomic<float> targetAngle;
};

#endif /* SRC_ELEVATORCONTROLLER_H_ */
