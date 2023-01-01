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
	outLap = 3,
};

enum RaceStatus : uint8_t
{
	traning = 1,
	qualify = 2,
	Race = 3,
	formationLap = 4,
	endQualify = 5,
	checkDistanceSensor = 6
};

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address, if it's not working try 0x27.
VL53L0X sensor;

unsigned long startMillis = 0;
unsigned long elapsedMillis = 0;
unsigned long currentMillis = 0;
unsigned long recordMillis = 0;
unsigned long recordBeforeMillis = 0;
LapStatus lapStatus = LapStatus::pitLane;
RaceStatus raceStatus = RaceStatus::Race;
unsigned long qualifyTimeLimits = 0;
uint8_t qualifyNumberLaps = 5;
int8_t lap = 0;
int8_t lapBeforeQualify = 2;
bool isDisableTone = false;
char macchineName[6] = "Ferr.";
uint8_t  numbersOfTotalRaceLap = 10;
uint8_t  numbersOfActualRaceLap = 0;
#define pinLed 9

void setup()
{
	Serial.begin(9600);
	Wire.begin();
	pinMode(pinLed, OUTPUT);
	if (!sensor.init())
	{
		Serial.println(F("error sensor!"));
		while (1) {}
	}
	// Start continuous back-to-back mode (take readings as
	// fast as possible).  To use continuous timed mode
	// instead, provide a desired inter-measurement period in
	// ms (e.g. sensor.startContinuous(100)).
	/*sensor.startContinuous();*/
	sensor.setMeasurementTimingBudget(20000);
	sensor.startContinuous();
	lcd.begin(16, 2);   // iInit the LCD for 16 chars 2 lines
	lcd.backlight();   // Turn on the backligt (try lcd.noBaklight() to turn it off)
}

void soundInitQualify()
{
	if (isDisableTone) return;
	tone(8, 500, 50);
	delay(100);
	tone(8, 500, 50);
	delay(100);
	tone(8, 500, 50);
	delay(100);
	noTone(8);
}

void soundEndQualify()
{
	if (isDisableTone) return;
	tone(8, 1500, 4000);
	delay(3000);
	noTone(8);
}

void soundPhotoFinish()
{
	if (isDisableTone) return;
	tone(8, 2000, 50);
	delay(50);
	tone(8, 1500, 50);
	delay(50);
	tone(8, 2500, 50);
	delay(50);
	tone(8, 3000, 50);
	delay(50);
	tone(8, 2000, 50);
	delay(50);
	tone(8, 1500, 50);
	delay(50);
	tone(8, 2500, 50);
	delay(50);
	tone(8, 3000, 50);
	delay(50);
	noTone(8);
}

//void soundToContruct()
//{
//	if (isDisableTone) return;
//	tone(8, 100, 200);
//	delay(200);
//	tone(8, 200, 200);
//	delay(200);
//	tone(8, 500, 200);
//	delay(200);
//	tone(8, 100, 200);
//	delay(200);
//	noTone(8);
//}

void soundStartRace()
{
	tone(8, 500, 1000);
	delay(2000);
	tone(8, 500, 1000);
	delay(2000);
	tone(8, 500, 1000);
	delay(2000);
	tone(8, 1000, 1000);
	delay(2000);
	noTone(8);
}

void detectTransitCar()
{
	int distance = sensor.readRangeContinuousMillimeters();
	if (sensor.timeoutOccurred()) { lcdPrintMessage(F("sensor error"), 0, 4,false); }
	if ((distance < 100 && distance > 10) )
	{
		if (lapStatus == LapStatus::outLap && lap == qualifyNumberLaps) {
			lapStatus = LapStatus::finishLine;
			currentMillis = millis();
			lap = -2;
			setRecordsAndDisplayTime();
			startMillis = 0;
		}
		//starter for qualify
		else if(startMillis == 0 && lap >= 0) {
			startMillis = millis();
			lapStatus = LapStatus::outLap;
			lcdPrintMessage(F("out of lap"), 0, 4,true);
			soundInitQualify();
		}
		lap++;
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
		if (isCarTransit())
		{
			raceManager();
		}
		break;
	case endQualify:
		lcdSlideMessage("End qualify session ....");
		setRecordsAndDisplayTime();
		delay(5000);
		break;
	case formationLap:
		break;
	case checkDistanceSensor:
		break;
	default:
		break;
	}
}

void traningStatusManager()
{
	lcdSlideMessage(F("Cars in the paddock"));
}

void qualityStatusManager()
{
	if (qualifyTimeLimits != 0 && ((millis() - qualifyTimeLimits) > (5ul * 60ul * 1000ul)))
	{
		soundEndQualify();
		lcdPrintMessage(F("End qualify"), 0, 0, true);
		raceStatus = RaceStatus::endQualify;
	/*	setRecordsAndDisplayTime();*/
		qualifyTimeLimits = 0;
	}

	switch (lapStatus)
	{
	case pitLane:
		lcdPrintMessage(F("Cars in pit lane"),0,0,false);
		lcdPrintMessage(F("Session qualify"),1, 0, false);
		break;
	case finishLine:
		break;
	case outLap:
		if (qualifyTimeLimits == 0)
		{
			qualifyTimeLimits = millis();
			/*soundInitQualify();*/
		}
	/*	else
		{
			if ((millis() - qualifyTimeLimits) > (1ul*3ul*1000ul))
			{
				soundEndQualify();
				lcdPrintMessage(F("End qualify"), 0, 0, true);
				lapStatus = LapStatus::pitLane;
				qualifyTimeLimits = 0;
			}
		}*/
		break;
	default:
		break;
	}
}

void raceManager()
{
		String stringToDisplay = macchineName;
		stringToDisplay.concat("lap. :");
		stringToDisplay.concat(numbersOfActualRaceLap);
		lcdPrintMessage(stringToDisplay, 0, 0, true);
		numbersOfActualRaceLap++;
		if (numbersOfActualRaceLap == (numbersOfTotalRaceLap - ((numbersOfTotalRaceLap  * 20) / 100)))
		{
			soundPhotoFinish();
		}
	//else if (carNumber == 2)
	//{
	//	String a = "Merc.Lap :";
	//	a.concat(numbersOfRaceLapSecond);
	//	lcdPrintMessage(a, 0, 0, true);
	//	numbersOfRaceLapSecond++;
	//}
	if (numbersOfActualRaceLap >= numbersOfTotalRaceLap)
	{
		lcd.clear();
		lcdPrintMessage(F("End race"), 0, 0, false);
		soundEndQualify();
		while (1) {};
	}
	//if (numbersOfRaceLapSecond >= 5)
	//{
	//	lcd.clear();
	//	lcdPrintMessage(F("Second WIN"), 0, 0, false);
	//	delay(100000000);
	//}
}

bool isCarTransit()
{
	if (sensor.timeoutOccurred()) { lcdPrintMessage(F("sensor error"), 0, 4, false); }
	int distance = sensor.readRangeContinuousMillimeters();
	if ((distance < 60 && distance > 10))
	{
		digitalWrite(9, HIGH);
		delay(1000);
		digitalWrite(9, LOW);
		distance = sensor.readRangeContinuousMillimeters();
		if(distance > 100) return true;
	}
	return false;
}

void lcdPrintMessage(String message,uint8_t row,uint8_t col ,bool clear)
{
	if(clear) lcd.clear();
	lcd.setCursor(col,row); //First line
	lcd.print(message);
}

void lcdSlideMessage(String message) {
	lcd.clear();
	lcd.setCursor(16, 0); //First line
	lcd.scrollDisplayLeft();
	lcd.autoscroll();
	for (int thisChar = 0; thisChar < message.length(); thisChar++) {
		lcd.print(message.charAt(thisChar));
		delay(300);
	}
	delay(1000);
	lcd.clear();
}

void setRecordsAndDisplayTime()
{
	if (raceStatus != RaceStatus::endQualify)
	{
		elapsedMillis = (currentMillis - startMillis);
		/*if (elapsedMillis < 1000) {
			lcdPrintMessage("reset system",0,0);
			return;
		} */
		if (recordMillis == 0) {
			recordMillis = elapsedMillis;
		}
		//when made a record
		if (elapsedMillis < recordMillis) {
			recordBeforeMillis = recordMillis;
			recordMillis = elapsedMillis;
		}
		else {
			elapsedMillis = recordMillis;
		}
	}
	else
	{
		elapsedMillis = recordMillis;
	}
	lcd.begin(16, 2);
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(F("Leclerc Ferr."));
	
	/*lcd.print("                ");*/


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
