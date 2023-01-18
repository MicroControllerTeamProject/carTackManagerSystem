#include "CarTrackBusinessLayer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef _DEBUG
#include <Arduino.h>
#endif

uint8_t  numbersOfTotalRaceLap = 50;
uint8_t  numbersOfActualRaceLap = 0;

CarTrackBusinessLayer::CarTrackBusinessLayer(
	InterfaceObstacleActivity* irObstacleSensorActivity,AvrMicroRepository& avrMicroRepository) {
	this->avrMicroRepository = &avrMicroRepository;
	this->_interfaceObstacleActivity = irObstacleSensorActivity;
}


void CarTrackBusinessLayer::startRace()
{
	while (numbersOfActualRaceLap < numbersOfTotalRaceLap)
	{

		if (isDetectedTransitCar())
		{
			char laps[10] = {};
			numbersOfActualRaceLap++;
			sprintf(laps, "%d", numbersOfActualRaceLap);
#ifdef _DEBUG
			Serial.print("lap : "); Serial.println(laps);
#endif
		}
	/*	#ifdef _DEBUG
				char d[10] = {};
				Serial.print("ram:"); Serial.println(itoa(this->avrMicroRepository->getFreeRam(), d, 10));
		#endif*/
	}
	numbersOfActualRaceLap = 0;
}

bool CarTrackBusinessLayer::isDetectedTransitCar()
{
	return this->_interfaceObstacleActivity->isObstacleDetected("irObstPort1");
}






