#pragma once
#include "\Repos\MicroControllerTeamProject\ActivityFramework\activity\IRObstacleSensorActivity.h"
#include "\Repos\MicroControllerTeamProject\ActivityFramework\activity\LiquidCristalI2cActivity.h"
#include "\Repos\MicroControllerTeamProject\ActivityFramework\activity\SwitchActivity.h"
#include "\Repos\MicroControllerTeamProject\ActivityFramework\activity\RFReceiverActivity.h"
#include "\Repos\MicroControllerTeamProject\ActivityFramework\activity\BuzzerActivity.h"
#include "\Repos\MicroControllerTeamProject\ActivityFramework\repository\AvrMicroRepository.h"
#include "\Repos\MicroControllerTeamProject\ActivityFramework\interfaces\InterfaceObstacleActivity.h"


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

