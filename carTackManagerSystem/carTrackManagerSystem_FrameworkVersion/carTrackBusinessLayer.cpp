#include "carTrackBusinessLayer.h"

uint8_t lapRaceNumbers = 30;

CarTrackBusinessLayer::CarTrackBusinessLayer(LiquidCristalI2cActivity* liquidCristalI2cActivity,
	IRObstacleSensorActivity* irObstacleSensorActivity,SwitchActivity* switchActivity){
	this->_liquidCristalI2cActivity = liquidCristalI2cActivity;
	this->_irObstacleSensorActivity = irObstacleSensorActivity;
	this->_switchActivity = switchActivity;
}

void CarTrackBusinessLayer::displayLogo(){
	this->_liquidCristalI2cActivity->print("LSG-Software",0,0,true);
}

bool CarTrackBusinessLayer::isDetectedTransitCar()
{
	this->_irObstacleSensorActivity->isObstacleDetected();
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
		
		this->_liquidCristalI2cActivity->print("switch detected", 0, 0, true);
		this->_switchActivity->avrMicroRepository->delaym(1000);
		this->_liquidCristalI2cActivity->print(" ", 0, 0, true);
	}


	if (this->_irObstacleSensorActivity->isObstacleDetected())
	{
		this->_liquidCristalI2cActivity->print("car detected",0,0,true);
		this->_switchActivity->avrMicroRepository->delaym(1000);
		this->_liquidCristalI2cActivity->print(" ", 0, 0, true);

	}
}
//
//void CarTrackBusinessLayer::detectTransitCar(IRObstacleSensorActivity irObstacleSensorActivity,AvrMicroRepository avrMicroRepository)
//{
//	irObstacleSensorActivity.isObstacleDetected(avrMicroRepository);
//}






