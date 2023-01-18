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
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\repository\VL53L0XRepository.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\repository\RFReceiverRepository.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\repository\LiquidCristalI2CRepository.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\LiquidCristalI2cActivity.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\SwitchActivity.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\RFReceiverActivity.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\BuzzerActivity.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\VL53L0XActivity.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\model\DigitalPort.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\interfaces\InterfaceObstacleActivity.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\objectsSensor\DigitalPortSensor.h>
#include <\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\objectsSensor\I2COstacleSensor.h>
#include <stdint.h>
#include "CarTrackBusinessLayer.h"


#define RF433_RX_PIN 4
#define RACE_SWITCH_PIN 6
#define IR_OSTACLE_PIN 7
#define BUZZER_PIN 8

AvrMicroRepository avrMicroRepository;
VL53L0XRepository vl53L0XRepository;
CarTrackBusinessLayer* carTrackBusinessLayer;
IRObstacleSensorActivity* irObstacleSensorActivity;
VL53L0XActivity* vl53L0XActivity;


DigitalPort* irObstaclePorts[2];
DigitalPortSensor* irObstacleSensor[1]{};

I2COstacleSensor* listOfi2COstacleSensor[2];

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.println("RESTART");

	listOfi2COstacleSensor[0] = new I2COstacleSensor(41,70,300);
	listOfi2COstacleSensor[0]->enable(true);

	listOfi2COstacleSensor[1] = new I2COstacleSensor(42, 70, 300);
	listOfi2COstacleSensor[1]->enable(true);

	irObstaclePorts[0] = new DigitalPort("irObstPort1", IR_OSTACLE_PIN);
	irObstaclePorts[0]->direction = DigitalPort::PortDirection::input;
	irObstaclePorts[0]->alarmTriggerOn = DigitalPort::AlarmOn::low;
	irObstaclePorts[0]->isOnPullUp = true;

	irObstaclePorts[1] = new DigitalPort("irObstPort2", IR_OSTACLE_PIN);
	irObstaclePorts[1]->direction = DigitalPort::PortDirection::input;
	irObstaclePorts[1]->alarmTriggerOn = DigitalPort::AlarmOn::low;
	irObstaclePorts[1]->isOnPullUp = true;


	irObstacleSensor[0] = new DigitalPortSensor(irObstaclePorts,sizeof(irObstaclePorts) / sizeof(irObstaclePorts[0]));
	irObstacleSensor[0]->setUid("Obs.Sens.01");
	irObstacleSensor[0]->enable(true);

	irObstacleSensorActivity = new IRObstacleSensorActivity(avrMicroRepository,irObstacleSensor,(sizeof(irObstacleSensor)/sizeof(irObstacleSensor[0])));
	
	vl53L0XActivity = new VL53L0XActivity(vl53L0XRepository, listOfi2COstacleSensor, sizeof(listOfi2COstacleSensor) / sizeof(listOfi2COstacleSensor[0]));
	
	carTrackBusinessLayer = new CarTrackBusinessLayer(vl53L0XActivity,avrMicroRepository);

	//carTrackBusinessLayer = new CarTrackBusinessLayer(irObstacleSensorActivity, avrMicroRepository);
}

void loop() {
		carTrackBusinessLayer->startRace();
}


