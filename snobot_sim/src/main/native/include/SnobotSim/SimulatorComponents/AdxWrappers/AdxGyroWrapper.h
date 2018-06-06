/*
 * AdxGyroWrapper.h
 *
 *  Created on: Nov 23, 2017
 *      Author: PJ
 */

#ifndef SNOBOTSIM_SNOBOT_SIM_SRC_MAIN_NATIVE_INCLUDE_SNOBOTSIM_SIMULATORCOMPONENTS_ADXWRAPPERS_ADXGYROWRAPPER_H_
#define SNOBOTSIM_SNOBOT_SIM_SRC_MAIN_NATIVE_INCLUDE_SNOBOTSIM_SIMULATORCOMPONENTS_ADXWRAPPERS_ADXGYROWRAPPER_H_

#include <memory>

#include "ADXRS450_SpiGyroWrapperData.h"
#include "SnobotSim/SimulatorComponents/Gyro/IGyroWrapper.h"
#include "SnobotSim/SimulatorComponents/Spi/ISpiWrapper.h"

class AdxGyroWrapper : public ISpiWrapper, public IGyroWrapper
{
public:
    explicit AdxGyroWrapper(int aPort);
    virtual ~AdxGyroWrapper();

    void SetAngle(double aAngle) override;

    double GetAngle() override;

protected:
    std::shared_ptr<hal::ADXRS450_SpiGyroWrapper> mGyro;
};

#endif // SNOBOTSIM_SNOBOT_SIM_SRC_MAIN_NATIVE_INCLUDE_SNOBOTSIM_SIMULATORCOMPONENTS_ADXWRAPPERS_ADXGYROWRAPPER_H_
