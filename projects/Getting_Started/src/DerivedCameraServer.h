/*
 * DerivedCameraServer.h
 *
 *  Created on: Feb 15, 2015
 *      Author: FRC812
 */

#ifndef SRC_DERIVEDCAMERASERVER_H_
#define SRC_DERIVEDCAMERASERVER_H_

class DerivedCameraServer : public CameraServer {
public:
	virtual ~DerivedCameraServer();

	static DerivedCameraServer* GetInstance();
	void setExposureAuto();

private:
	DerivedCameraServer();
	static DerivedCameraServer* instance;

};

#endif /* SRC_DERIVEDCAMERASERVER_H_ */
