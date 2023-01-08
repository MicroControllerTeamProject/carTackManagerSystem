#include "carTrackBusinessLayer.h"
#include <string.h>
#include <stdlib.h>


uint8_t  numbersOfTotalRaceLap = 5;
uint8_t  numbersOfActualRaceLap = 0;

CarTrackBusinessLayer::CarTrackBusinessLayer(LiquidCristalI2cActivity* liquidCristalI2cActivity,
	IRObstacleSensorActivity* irObstacleSensorActivity/*,SwitchActivity* switchActivity*/){
	this->_liquidCristalI2cActivity = liquidCristalI2cActivity;
	this->_irObstacleSensorActivity = irObstacleSensorActivity;

}

void CarTrackBusinessLayer::displayLogo(){
	this->_liquidCristalI2cActivity->print("LSG-Software",0,0,true,0);
}

//void CarTrackBusinessLayer::setRaceConfiguration(AvrMicroRepository& avrMicroRepository)
//{
//	if (avrMicroRepository.digitalReadm(RacePin) == HIGH)
//	{
//		this->raceConfiguration = commonLayer::RaceConfiguration::Race;
//	}
//	this->raceConfiguration = commonLayer::RaceConfiguration::Traning;
//}
//
//commonLayer::RaceConfiguration CarTrackBusinessLayer::getRaceConfiguration()
//{
//	return this->raceConfiguration;
//}
//

void CarTrackBusinessLayer::startCompetition()
{
		startRace();
}

void CarTrackBusinessLayer::startRace()
{
	while (true)
	{
		if (isDetectedTransitCar())
		{
			char laps[10] = {};
			numbersOfActualRaceLap++;
			itoa((int)numbersOfActualRaceLap, laps, 10);
			this->_liquidCristalI2cActivity->print("                ", 0, 1, false, 0);
			this->_liquidCristalI2cActivity->print("lap : ",0,1,false,0);
			this->_liquidCristalI2cActivity->print(laps, 7, 1, false, 500);
		}
	}
}

bool CarTrackBusinessLayer::isDetectedTransitCar()
{
	return this->_irObstacleSensorActivity->isObstacleDetected("irObst1");
}






