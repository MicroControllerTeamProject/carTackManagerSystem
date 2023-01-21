
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\repository\AvrMicroRepository.h"
//#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\repository\RFReceiverRepository.h"
//#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\repository\LiquidCristalI2CRepository.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\model\DigitalPort.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\model\AnalogPort.h"
//#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\SwitchActivity.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\DeviceActivity.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\IRObstacleSensorActivity.h"
//#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\LiquidCristalI2cActivity.h"
//#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\RFReceiverActivity.h"
//#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\BuzzerActivity.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\interfaces\InterfaceObstacleActivity.h"
#include "..\carTrackManagerSystem_FrameworkVersion\CarTrackBusinessLayer.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\objectsSensor\DigitalPortSensor.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\objectsSensor\AnalogPortSensor.h"

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

			IRObstacleSensorActivity* irObstacleSensorActivity;
			
			DigitalPort* irObstaclePorts[2] = {};

			DigitalPortSensor* irObstacleSensor[1]{};

			irObstaclePorts[0] = new DigitalPort("irObstPort1", 7);
			irObstaclePorts[0]->direction = DigitalPort::PortDirection::input;
			irObstaclePorts[0]->alarmTriggerOn = DigitalPort::AlarmOn::low;
			irObstaclePorts[0]->isOnPullUp = true;

			irObstacleSensor[0] = new DigitalPortSensor("Obs.Sens.01", irObstaclePorts, sizeof(irObstaclePorts) / sizeof(irObstaclePorts[0]));
			/*irObstacleSensor[0]->setUid("Obs.Sens.01");*/
			irObstacleSensor[0]->enable(true);

			When(Method(mockedAvrMicroRepository, digitalReadm)).Return(0,1);
			When(Method(mockedAvrMicroRepository, pinMode_m)).AlwaysReturn();
			When(Method(mockedAvrMicroRepository, delaym)).AlwaysReturn();

			irObstacleSensorActivity = new IRObstacleSensorActivity(mainRepository, irObstacleSensor, (sizeof(irObstacleSensor) / sizeof(irObstacleSensor[0])));
			
			CarTrackBusinessLayer carTrackBusinessLayer(irObstacleSensorActivity, mainRepository); 

			bool returnValue = carTrackBusinessLayer.isDetectedTransitCar("irObstPort1");

			Assert::AreEqual(true, returnValue);
		}
	};
}
