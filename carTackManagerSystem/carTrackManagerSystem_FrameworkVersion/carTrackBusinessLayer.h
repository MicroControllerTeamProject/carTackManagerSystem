#pragma once
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\IRObstacleSensorActivity.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\LiquidCristalI2cActivity.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\repository\AvrMicroRepository.h"
#include "commonLayer.h"

class CarTrackBusinessLayer
{
public:
	CarTrackBusinessLayer(
		LiquidCristalI2cActivity* liquidCristalI2cActivity,
		IRObstacleSensorActivity* irObstacleSensorActivity
		/*AvrMicroRepository& avrMicroRepository,
		IRObstacleSensorActivity irObstacleSensorActivity*/);

	void displayLogo();
	bool isDetectedTransitCar();
	void startCompetition();
/*	void displayLogo(LiquidCristalI2cActivity* liquidCristalI2cActivity);
	void setRaceConfiguration(AvrMicroRepository& avrMicroRepository);
	commonLayer::RaceConfiguration getRaceConfiguration();

	void detectTransitCar(IRObstacleSensorActivity irObstacleSensorActivity,*/ /*AvrMicroRepository avrMicroRepository);*/
private:
	LiquidCristalI2cActivity* _liquidCristalI2cActivity;
	IRObstacleSensorActivity* _irObstacleSensorActivity;
	commonLayer::RaceConfiguration raceConfiguration;
};

