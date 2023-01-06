/*
 Name:		carTrackManagerSystem_FrameworkVersion.ino
 Created:	1/1/2023 4:42:44 PM
 Author:	luigi.santagada
*/

//#ifndef RAMSTART
//extern int __data_start;
//#endif
//
//extern int __data_end;
////extern int __bss_start;
////extern int __bss_end;
//extern int __heap_start;
//extern int __brkval;
//int temp;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\repository\AvrMicroRepository.h>
//#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\repository\LiquidCristalI2CRepository.h>
//#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\LiquidCristalI2cActivity.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\SwitchActivity.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\model\DigitalPort.h>
#include <stdint.h>
#include "carTrackBusinessLayer.h"

AvrMicroRepository avrMicroRepository;
CarTrackBusinessLayer* carTrackBusinessLayer;
LiquidCristalI2cActivity* liquidCristalI2cActivity;
LiquidCristalI2CRepository* liquidCristalI2CRepository;
IRObstacleSensorActivity* irObstacleSensorActivity;
SwitchActivity* switchActivity;
DigitalPort** irObstaclePorts;
DigitalPort** switchPorts;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	Serial.println("Start");

	switchPorts = new DigitalPort * [2];
	switchPorts[0] = new DigitalPort("swRace01", 6);
	switchPorts[0]->direction = DigitalPort::PortDirection::input;
	switchPorts[0]->alarmTriggerOn = DigitalPort::AlarmOn::low;
	switchPorts[0]->isOnPullUp = true;
	switchPorts[1] = new DigitalPort("swtch2", 10);
	switchPorts[1]->direction = DigitalPort::PortDirection::input;
	switchPorts[1]->alarmTriggerOn = DigitalPort::AlarmOn::low;
	switchPorts[1]->isOnPullUp = true;

	switchActivity = new SwitchActivity(avrMicroRepository, switchPorts, 2);

	liquidCristalI2CRepository = new LiquidCristalI2CRepository(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, 0);
	liquidCristalI2cActivity = new LiquidCristalI2cActivity(liquidCristalI2CRepository, 16, 2);

	irObstaclePorts = new DigitalPort * [1];
	irObstaclePorts[0] = new DigitalPort("irObst1", 7);
	irObstaclePorts[0]->direction = DigitalPort::PortDirection::input;
	irObstaclePorts[0]->alarmTriggerOn = DigitalPort::AlarmOn::low;
	irObstaclePorts[0]->isOnPullUp = true;
	irObstacleSensorActivity = new IRObstacleSensorActivity(avrMicroRepository, irObstaclePorts, 1);
	carTrackBusinessLayer = new CarTrackBusinessLayer(liquidCristalI2cActivity, irObstacleSensorActivity,switchActivity);
	carTrackBusinessLayer->displayLogo();
	
}


void loop() {
	carTrackBusinessLayer->startCompetition();

	char d[10] = {};
	itoa(avrMicroRepository.getFreeRam(), d, 10);
	/*delay(500);*/
	liquidCristalI2cActivity->print(d, 0, 1, false);
}


