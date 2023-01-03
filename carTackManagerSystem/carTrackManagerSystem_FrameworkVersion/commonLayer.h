#pragma once
#include <stdint.h>

class commonLayer
{
public:
	enum RaceConfiguration : uint8_t
	{
		Qualify = 1,
		Race = 2,
		Traning = 3
	};

	enum LapStatus : uint8_t
	{
		SafetyCar = 1,
		FinishLine = 2,
		OutLap = 3,
	};

	/*enum RaceStatus : uint8_t
	{
		traning = 1,
		qualify = 2,
		Race = 3,
		formationLap = 4,
		endQualify = 5,
		checkDistanceSensor = 6
	};*/
};

