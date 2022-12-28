/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm.

Original source: https://github.com/pololu/vl53l0x-arduino

High speed
https://forum.pololu.com/t/high-speed-with-vl53l0x/16585

Modified by Ahmad Shamshiri for RoboJax.com
Date mortified: Sep 26, 2017
*/
/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.
The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>
#include <LiquidCrystal_I2C.h>

enum LapStatus : uint8_t
{
	pitLane = 1,
	finishLine = 2,
	outLap = 3
};

enum RaceStatus : uint8_t
{
	traning = 1,
	qualify = 2,
	Race = 3,
	formationLap = 4
};

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address, if it's not working try 0x27.
VL53L0X sensor;

unsigned long startMillis = 0;
unsigned long elapsedMillis = 0;
unsigned long currentMillis = 0;
unsigned long recordMillis = 0;
unsigned long recordBeforeMillis = 0;
LapStatus lapStatus = LapStatus::pitLane;
RaceStatus raceStatus = RaceStatus::qualify;
unsigned long qualifyTimeLimits = 0;

void setup()
{
	Serial.begin(9600);
	Wire.begin();
	pinMode(9, OUTPUT);
	if (!sensor.init())
	{
		Serial.println("Failed to detect and initialize sensor!");
		while (1) {}
	}
	// Start continuous back-to-back mode (take readings as
	// fast as possible).  To use continuous timed mode
	// instead, provide a desired inter-measurement period in
	// ms (e.g. sensor.startContinuous(100)).
	/*sensor.startContinuous();*/
	sensor.setMeasurementTimingBudget(20000);
	sensor.startContinuous();
	lcd.begin(16, 1);   // iInit the LCD for 16 chars 2 lines
	tone(8, 500, 500);
	delay(1000);
	noTone(8);
}

void detectTransitCar()
{
	int distance = sensor.readRangeContinuousMillimeters();
	if (sensor.timeoutOccurred()) { lcdPrintMessage("sensor error", 0, 4,false); }
	if (distance < 100 && distance > 10)
	{
		if (lapStatus == LapStatus::outLap) {
			lapStatus = LapStatus::finishLine;
			currentMillis = millis();
			setRecordsAndDisplayTime();
		}
		else {
			startMillis = millis();
			lapStatus = LapStatus::outLap;
			lcdPrintMessage(F("out of lap"), 0, 4,true);
		}
		digitalWrite(9, HIGH);
		delay(500);
	}
	else
	{
		digitalWrite(9, LOW);
	}
}

void loop()
{
	switch (raceStatus)
	{
	case traning:
		traningStatusManager();
		break;
	case qualify:
		qualityStatusManager();
		detectTransitCar();
		break;
	case Race:
		break;
	case formationLap:
		break;
	default:
		break;
	}
}

void traningStatusManager()
{
	lcdSlideMessage(F("waiting for race!"));
	
}

void qualityStatusManager()
{
	switch (lapStatus)
	{
	case pitLane:
		lcdPrintMessage(F("Cars in pit lane."),0,0,false);
		break;
	case finishLine:
		break;
	case outLap:
		if (qualifyTimeLimits == 0)
		{
			qualifyTimeLimits == millis();
		}
		else
		{
			if ((millis() - qualifyTimeLimits) > 15 * 60 * 1000);
			lapStatus = LapStatus::pitLane;
		}
		break;
	default:
		break;
	}
}

void lcdPrintMessage(String message,uint8_t row,uint8_t col ,bool clear)
{
	if(clear) lcd.clear();

	lcd.backlight();   // Turn on the backligt (try lcd.noBaklight() to turn it off)
	lcd.setCursor(col,row); //First line
	lcd.print(message);
}

void lcdSlideMessage(String message) {
	lcd.begin(16, 1);   // iInit the LCD for 16 chars 2 lines
	lcd.backlight();   // Turn on the backligt (try lcd.noBaklight() to turn it off)
	lcd.setCursor(16, 1); //First line
	lcd.scrollDisplayLeft();
	lcd.autoscroll();
	for (int thisChar = 0; thisChar < message.length(); thisChar++) {
		lcd.print(message.charAt(thisChar));
		delay(250);
	}
	delay(2000);
	lcd.clear();
}

void setRecordsAndDisplayTime()
{
	elapsedMillis = (currentMillis - startMillis);

	/*if (elapsedMillis < 1000) {
		lcdPrintMessage("reset system",0,0);
		return;
	} */

	if (recordMillis == 0){
		recordMillis = elapsedMillis;
	}
	//when made a record
	if(elapsedMillis < recordMillis){
		recordBeforeMillis = recordMillis;
		recordMillis = elapsedMillis;
	}
	else{
		elapsedMillis = recordMillis;
	}

	lcd.setCursor(0, 0);
	lcd.print("SW (hh:mm:ss:ms)");
	lcd.setCursor(0, 1);
	lcd.print("                ");


	unsigned long durMS = (elapsedMillis % 1000);       //Milliseconds
	unsigned long durSS = (elapsedMillis / 1000) % 60;    //Seconds
	unsigned long durMM = (elapsedMillis / (60000)) % 60; //Minutes
	unsigned long durHH = (elapsedMillis / (3600000));  //Hours
	durHH = durHH % 24;

	String durMilliSec = timeMillis(durHH, durMM, durSS, durMS);
	lcd.setCursor(0, 1);
	lcd.print(durMilliSec);
	delay(150);
}

String timeMillis(unsigned long Hourtime, unsigned long Mintime, unsigned long Sectime, unsigned long MStime)
{
	String dataTemp = "";

	if (Hourtime < 10)
	{
		dataTemp = dataTemp + "0" + String(Hourtime) + "h:";
	}
	else {
		dataTemp = dataTemp + String(Hourtime) + "h:";
	}

	if (Mintime < 10)
	{
		dataTemp = dataTemp + "0" + String(Mintime) + "m:";
	}
	else {
		dataTemp = dataTemp + String(Mintime) + "m:";
	}

	if (Sectime < 10)
	{
		dataTemp = dataTemp + "0" + String(Sectime) + "s:";
	}
	else {
		dataTemp = dataTemp + String(Sectime) + "s:";
	}

	dataTemp = dataTemp + String(MStime);

	return dataTemp;
}
