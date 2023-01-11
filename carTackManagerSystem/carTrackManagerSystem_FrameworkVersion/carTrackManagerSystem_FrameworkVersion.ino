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

#include <VL53L0X.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\repository\AvrMicroRepository.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\repository\RFReceiverRepository.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\repository\LiquidCristalI2CRepository.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\LiquidCristalI2cActivity.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\SwitchActivity.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\RFReceiverActivity.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\BuzzerActivity.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\model\DigitalPort.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\interfaces\InterfaceObstacleActivity.h>
#include <stdint.h>
#include "CarTrackBusinessLayer.h"

#define RF433_RX_PIN 4
#define RACE_SWITCH_PIN 6
#define IR_OSTACLE_PIN 7
#define BUZZER_PIN 8

AvrMicroRepository avrMicroRepository;
CarTrackBusinessLayer* carTrackBusinessLayer;
LiquidCristalI2cActivity* liquidCristalI2cActivity;
LiquidCristalI2CRepository* liquidCristalI2CRepository;
IRObstacleSensorActivity* irObstacleSensorActivity;
BuzzerActivity* buzzerActivity;

SwitchActivity* switchActivity;
DigitalPort** irObstaclePorts;
DigitalPort** switchPorts;
DigitalPort** buzzerPorts;

RFReceiverRepository rfReceiverRepository(RF433_RX_PIN, 99, 100);
RFReceiverActivity* rfReceiverActivity = new RFReceiverActivity(rfReceiverRepository);

// the setup function runs once when you press reset or power the board
void setup() {

	switchPorts = new DigitalPort * [1];
	switchPorts[0] = new DigitalPort("swRace01", RACE_SWITCH_PIN);
	switchPorts[0]->direction = DigitalPort::PortDirection::input;
	switchPorts[0]->alarmTriggerOn = DigitalPort::AlarmOn::low;
	switchPorts[0]->isOnPullUp = true;
	switchActivity = new SwitchActivity(avrMicroRepository, switchPorts, 1);


	liquidCristalI2CRepository = new LiquidCristalI2CRepository(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, 0);
	liquidCristalI2cActivity = new LiquidCristalI2cActivity(liquidCristalI2CRepository, 16, 2);


	irObstaclePorts = new DigitalPort * [1];
	irObstaclePorts[0] = new DigitalPort("irObst1", IR_OSTACLE_PIN);
	irObstaclePorts[0]->direction = DigitalPort::PortDirection::input;
	irObstaclePorts[0]->alarmTriggerOn = DigitalPort::AlarmOn::low;
	irObstaclePorts[0]->isOnPullUp = true;
	irObstacleSensorActivity = new IRObstacleSensorActivity(avrMicroRepository, irObstaclePorts, 1);
	buzzerPorts = new DigitalPort * [1];
	buzzerPorts[0] = new DigitalPort("buzz01", BUZZER_PIN);
	buzzerPorts[0]->direction = DigitalPort::PortDirection::output;
	buzzerPorts[0]->isEnable = false;
	buzzerActivity = new BuzzerActivity(avrMicroRepository, buzzerPorts, 1);
	

	carTrackBusinessLayer = new CarTrackBusinessLayer(liquidCristalI2cActivity, 
		irObstacleSensorActivity,
		switchActivity,
		rfReceiverActivity,buzzerActivity);
	carTrackBusinessLayer->displayLogo();
}

bool check = false;

void loop() {
	if (carTrackBusinessLayer->isReceivedStartCommand())
	{
		carTrackBusinessLayer->startRace();
	}

	//if (rfReceiverActivity->isGotMessage("B0") && check == false)
	//{
	//	rfReceiverActivity->stop();
	//	delay(200);
	//	check = true;
	//}
	//if (check)
	//{
	//	liquidCristalI2cActivity->print("Race Started!", 0, 0, true, 0);
	//	/*char d[10] = {};
	//	itoa(avrMicroRepository.getFreeRam(), d, 10);*/
	//	/*delay(500);*/
	//	/*liquidCristalI2cActivity->print("Memory :", 0, 1, false, 0);
	//	liquidCristalI2cActivity->print(d, 9, 1, false, 0);*/
	//	carTrackBusinessLayer->startCompetition();
	//	rfReceiverActivity->begin();
	//	check = false;
	//}
}


