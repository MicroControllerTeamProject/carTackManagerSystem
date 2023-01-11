#include "CarTrackBusinessLayer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


uint8_t  numbersOfTotalRaceLap = 50;
uint8_t  numbersOfActualRaceLap = 0;

CarTrackBusinessLayer::CarTrackBusinessLayer(LiquidCristalI2cActivity* liquidCristalI2cActivity,
	InterfaceObstacleActivity* irObstacleSensorActivity,SwitchActivity* switchActivity,
	RFReceiverActivity* rfReceiverActivity,
	BuzzerActivity* buzzerActivity){

	this->_liquidCristalI2cActivity = liquidCristalI2cActivity;
	this->_interfaceObstacleActivity = irObstacleSensorActivity;
	this->_switchActivity = switchActivity;
	this->_rfReceiverActivity = rfReceiverActivity;
	this->_buzzerActivity = buzzerActivity;
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
	this->_rfReceiverActivity->stop();
	this->_liquidCristalI2cActivity->print("Race Started!", 0, 0, true, 0);
	this->_buzzerActivity->alarm3(2);
	while (numbersOfActualRaceLap < numbersOfTotalRaceLap)
	{
		
		if (isDetectedTransitCar())
		{
			if (numbersOfActualRaceLap == 0)
			{
				this->_buzzerActivity->alarm1(1);
			}
			char laps[10] = {};
			numbersOfActualRaceLap++;
			sprintf(laps,"%d", numbersOfActualRaceLap);
			/*itoa((int)numbersOfActualRaceLap, laps, 10);*/
			this->_liquidCristalI2cActivity->print("                ", 0, 1, false, 0);
			this->_liquidCristalI2cActivity->print("lap : ",0,1,false,0);
			this->_liquidCristalI2cActivity->print(laps, 7, 1, false, 500);
			if (numbersOfActualRaceLap == (numbersOfTotalRaceLap - ((numbersOfTotalRaceLap * 20) / 100)))
			{
				this->_buzzerActivity->alarm1(2);
			}
		}
	}
	numbersOfActualRaceLap = 0;
	this->_liquidCristalI2cActivity->print("Race finished!", 0, 0, true, 0);
	this->_buzzerActivity->alarm3(5);
}

bool CarTrackBusinessLayer::isReceivedStartCommand()
{
	this->_rfReceiverActivity->begin();
	if (this->_rfReceiverActivity->isGotMessage("B0") || this->_switchActivity->isSwitchOn("swRace01"))
	{
		this->_rfReceiverActivity->stop();
		return true;
	}
	return false;
}

bool CarTrackBusinessLayer::isDetectedTransitCar()
{
	return this->_interfaceObstacleActivity->isObstacleDetected("irObst1");
}






