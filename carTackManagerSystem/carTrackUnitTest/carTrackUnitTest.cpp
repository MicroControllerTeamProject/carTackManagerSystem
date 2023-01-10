
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\repository\AvrMicroRepository.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\repository\RFReceiverRepository.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\repository\LiquidCristalI2CRepository.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\model\DigitalPort.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\model\AnalogPort.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\SwitchActivity.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\DeviceActivity.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\IRObstacleSensorActivity.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\LiquidCristalI2cActivity.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\RFReceiverActivity.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\BuzzerActivity.h"
#include "..\carTrackManagerSystem_FrameworkVersion\CarTrackBusinessLayer.h"

#include "pch.h"
#include "CppUnitTest.h"
#include "src\extend.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace carTrackUnitTest
{
	TEST_CLASS(carTrackUnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Mock<AvrMicroRepository> mockedAvrMicroRepository;
			AvrMicroRepository& mainRepository = mockedAvrMicroRepository.get();

			DigitalPort** irObstaclePort = new  DigitalPort *[2];
			irObstaclePort[0] = new DigitalPort("IrOb1", 4);
			irObstaclePort[0]->alarmTriggerOn = DigitalPort::AlarmOn::low;
			irObstaclePort[0]->direction = DigitalPort::PortDirection::input;

	
			irObstaclePort[1] = new DigitalPort("IrOb2", 4);
			irObstaclePort[1]->alarmTriggerOn = DigitalPort::AlarmOn::high;
			irObstaclePort[1]->direction = DigitalPort::PortDirection::input;


			When(Method(mockedAvrMicroRepository, digitalReadm)).AlwaysReturn(1);
			When(Method(mockedAvrMicroRepository, pinMode_m)).AlwaysReturn();
			
			IRObstacleSensorActivity* iRObstacleSensorActivity = new IRObstacleSensorActivity(mainRepository,irObstaclePort,2);

			bool z = iRObstacleSensorActivity->isObstacleDetected("IrOb1");

			Assert::AreEqual(true, z);
		}
	};
}
