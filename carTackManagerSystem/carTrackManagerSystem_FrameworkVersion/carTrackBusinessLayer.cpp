#include "carTrackBusinessLayer.h"
#include <string.h>

uint8_t  numbersOfTotalRaceLap = 50;
uint8_t  numbersOfActualRaceLap = 0;

CarTrackBusinessLayer::CarTrackBusinessLayer(LiquidCristalI2cActivity* liquidCristalI2cActivity,
	IRObstacleSensorActivity* irObstacleSensorActivity){
	this->_liquidCristalI2cActivity = liquidCristalI2cActivity;
	this->_irObstacleSensorActivity = irObstacleSensorActivity;
}

void CarTrackBusinessLayer::displayLogo(){
	this->_liquidCristalI2cActivity->print("LSG-Software",0,0,true,0);
}

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
			this->_liquidCristalI2cActivity->print("car detected",0,0,true,500);
			this->_liquidCristalI2cActivity->print(" ", 0, 0, true,0);
		}
	}
}

bool CarTrackBusinessLayer::isDetectedTransitCar()
{
	return this->_irObstacleSensorActivity->isObstacleDetected("irObst1");
}






