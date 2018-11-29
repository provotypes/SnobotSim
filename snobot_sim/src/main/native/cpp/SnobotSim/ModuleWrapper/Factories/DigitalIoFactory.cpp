/*
 * DigitalIoFactory.cpp
 *
 *  Created on: Jun 30, 2018
 *      Author: PJ
 */

#include "SnobotSim/ModuleWrapper/Factories/DigitalIoFactory.h"

#include "SnobotSim/Logging/SnobotLogger.h"
#include "SnobotSim/ModuleWrapper/WpiWrappers/WpiDigitalIoWrapper.h"
#include "SnobotSim/SensorActuatorRegistry.h"

DigitalIoFactory::DigitalIoFactory()
{
}

DigitalIoFactory::~DigitalIoFactory()
{
}

bool DigitalIoFactory::Create(int aHandle, const std::string& aType)
{
    bool success = true;

    if (aType == "com.snobot.simulator.module_wrapper.wpi.WpiDigitalIoWrapper")
    {
        if (!SensorActuatorRegistry::Get().GetIDigitalIoWrapper(aHandle, false))
        {
            SNOBOT_LOG(SnobotLogging::LOG_LEVEL_WARN, "Not set up before loading robot");

            SensorActuatorRegistry::Get().Register(aHandle,
                    std::shared_ptr<IDigitalIoWrapper>(new WpiDigitalIoWrapper(aHandle)));
        }
    }
    else
    {
        SNOBOT_LOG(SnobotLogging::LOG_LEVEL_WARN, "Unknown type " << aType);
        success = false;
    }

    return success;
}
