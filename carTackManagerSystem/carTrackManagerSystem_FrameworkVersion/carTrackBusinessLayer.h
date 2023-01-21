#pragma once
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\IRObstacleSensorActivity.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\LiquidCristalI2cActivity.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\SwitchActivity.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\RFReceiverActivity.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\BuzzerActivity.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\repository\AvrMicroRepository.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\interfaces\InterfaceObstacleActivity.h"


class CarTrackBusinessLayer
{
public:
	CarTrackBusinessLayer(
		InterfaceObstacleActivity* irObstacleSensorActivity,AvrMicroRepository& avrMicroRepository
	);
	bool isDetectedTransitCar(char* sensorUid);
	void startRace();
	
private:
	InterfaceObstacleActivity* _interfaceObstacleActivity;
	AvrMicroRepository* avrMicroRepository = nullptr;
};

