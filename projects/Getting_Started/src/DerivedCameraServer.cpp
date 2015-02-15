/*
 * DerivedCameraServer.cpp
 *
 *  Created on: Feb 15, 2015
 *      Author: FRC812
 */

#include "WPILib.h"
#include <DerivedCameraServer.h>

DerivedCameraServer* DerivedCameraServer::instance = 0;

DerivedCameraServer::DerivedCameraServer() {
	// TODO Auto-generated constructor stub
	//CameraServer::CameraServer();
}

DerivedCameraServer* DerivedCameraServer::GetInstance(){
	if(instance == 0){
		instance = new DerivedCameraServer();
	}

	return instance;
}

DerivedCameraServer::~DerivedCameraServer() {
	// TODO Auto-generated destructor stub
}

void DerivedCameraServer::setExposureAuto(){
	this->m_camera->SetExposureAuto();
}

