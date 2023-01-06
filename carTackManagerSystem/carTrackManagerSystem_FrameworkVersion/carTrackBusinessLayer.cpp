#include "carTrackBusinessLayer.h"
#include <string.h>

uint8_t  numbersOfTotalRaceLap = 50;
uint8_t  numbersOfActualRaceLap = 0;

CarTrackBusinessLayer::CarTrackBusinessLayer(LiquidCristalI2cActivity* liquidCristalI2cActivity,
	IRObstacleSensorActivity* irObstacleSensorActivity,SwitchActivity* switchActivity){
	this->_liquidCristalI2cActivity = liquidCristalI2cActivity;
	this->_irObstacleSensorActivity = irObstacleSensorActivity;
	this->_switchActivity = switchActivity;
}

void CarTrackBusinessLayer::displayLogo(){
	this->_liquidCristalI2cActivity->print("LSG-Software",0,0,true);
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
	if (this->_switchActivity->isThereASwitchOn())
	{
		DigitalPort** listOfPorts = this->_switchActivity->getAllDigitalPorts();
		for (int i = 0; i < this->_switchActivity->digitalPortsNumber; i++)
		{
			if (listOfPorts[i]->isOnError && strcmp(listOfPorts[i]->getUid(),"swRace01") == 0)
			{
				startRace();
			}
		}
		
	}
}

void CarTrackBusinessLayer::startRace()
{
	while (true)
	{
		isDetectedTransitCar();
	}
}

bool CarTrackBusinessLayer::isDetectedTransitCar()
{
	return this->_irObstacleSensorActivity->isObstacleDetected("irObst1");
}






