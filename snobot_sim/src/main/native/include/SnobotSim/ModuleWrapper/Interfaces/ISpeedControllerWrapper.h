/*
 * ISpeedControllerWrapper.h
 *
 *  Created on: Jun 30, 2018
 *      Author: PJ
 */

#ifndef SNOBOTSIM_SNOBOT_SIM_SRC_MAIN_NATIVE_INCLUDE_SNOBOTSIM_MODULEWRAPPER_INTERFACES_ISPEEDCONTROLLERWRAPPER_H_
#define SNOBOTSIM_SNOBOT_SIM_SRC_MAIN_NATIVE_INCLUDE_SNOBOTSIM_MODULEWRAPPER_INTERFACES_ISPEEDCONTROLLERWRAPPER_H_

#include <memory>

#include "SnobotSim/MotorSim/IMotorSimulator.h"
#include "SnobotSim/SimulatorComponents/IFeedbackSensor.h"
#include "lowfisim/SimulatorComponent.h"

class ISpeedControllerWrapper : public virtual frc::sim::lowfi::SimulatorComponent
{
public:
    virtual int GetId() = 0;

    virtual void SetMotorSimulator(const std::shared_ptr<IMotorSimulator>& aSimulator) = 0;

    virtual const std::shared_ptr<IMotorSimulator>& GetMotorSimulator() = 0;

    virtual void SetFeedbackSensor(const std::shared_ptr<IFeedbackSensor>& aSimulator) = 0;

    virtual const std::shared_ptr<IFeedbackSensor>& GetFeedbackSensor() = 0;

    virtual double GetVoltagePercentage() = 0;

    virtual void SetVoltagePercentage(double aSpeed) = 0;

    virtual void Update(double aWaitTime) = 0;

    virtual double GetPosition() = 0;

    virtual double GetVelocity() = 0;

    virtual double GetCurrent() = 0;

    virtual double GetAcceleration() = 0;

    virtual void Reset() = 0;

    virtual void Reset(double aPosition, double aVelocity, double aCurrent) = 0;
};

#endif // SNOBOTSIM_SNOBOT_SIM_SRC_MAIN_NATIVE_INCLUDE_SNOBOTSIM_MODULEWRAPPER_INTERFACES_ISPEEDCONTROLLERWRAPPER_H_
