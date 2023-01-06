
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\repository\AvrMicroRepository.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\repository\LiquidCristalI2CRepository.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\model\DigitalPort.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\model\AnalogPort.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\SwitchActivity.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\IRObstacleSensorActivity.h"
#include "\Repos\MicroControllerTeamProject\Libraries\lsgNewFramework\activity\LiquidCristalI2cActivity.h"

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

			DigitalPort** irObstaclePort = new  DigitalPort *[1];
			irObstaclePort[0] = new DigitalPort("IrOb1", 4);
			irObstaclePort[0]->alarmTriggerOn = DigitalPort::AlarmOn::high;
			irObstaclePort[0]->direction = DigitalPort::PortDirection::input;




			/*Mock<AvrMicroRepository> mockedAvrMicroRepository;
			AvrMicroRepository& mainRepository = mockedAvrMicroRepository.get();

			DigitalPort** irObstaclePort = new  DigitalPort *[1];
			irObstaclePort[0] = new DigitalPort("IrOb1", 4);
			irObstaclePort[0]->alarmTriggerOn = DigitalPort::AlarmOn::high;
			irObstaclePort[0]->direction = DigitalPort::PortDirection::input;

			IRObstacleSensorActivity* iRObstacleSensorActivity = new IRObstacleSensorActivity(mainRepository,irObstaclePort,1);

			When(Method(mockedAvrMicroRepository, digitalReadm)).AlwaysReturn(1);*/


		}
	};
}
