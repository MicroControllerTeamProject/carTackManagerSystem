#pragma once
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\IRObstacleSensorActivity.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\LiquidCristalI2cActivity.h"
//#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\SwitchActivity.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\repository\AvrMicroRepository.h"

class CarTrackBusinessLayer
{
public:
	CarTrackBusinessLayer(
		LiquidCristalI2cActivity* liquidCristalI2cActivity,
		IRObstacleSensorActivity* irObstacleSensorActivity);
	void displayLogo();
	bool isDetectedTransitCar();
	void startCompetition();
	void startRace();
private:
	LiquidCristalI2cActivity* _liquidCristalI2cActivity;
	IRObstacleSensorActivity* _irObstacleSensorActivity;
};

