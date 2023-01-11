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
		LiquidCristalI2cActivity* liquidCristalI2cActivity,
		InterfaceObstacleActivity* irObstacleSensorActivity,
		SwitchActivity* switchActivity,
		RFReceiverActivity* rfReceiverActivity,
		BuzzerActivity* buzzerActivity
	);
	void displayLogo();
	bool isDetectedTransitCar();
	void startCompetition();
	void startRace();
	bool isReceivedStartCommand();
private:
	LiquidCristalI2cActivity* _liquidCristalI2cActivity;
	InterfaceObstacleActivity* _interfaceObstacleActivity;
	SwitchActivity* _switchActivity;
	RFReceiverActivity* _rfReceiverActivity;
	BuzzerActivity* _buzzerActivity;
};

