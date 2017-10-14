package com.snobot.simulator.simulator_components.gyro;

import com.snobot.simulator.jni.SensorFeedbackJni;
import com.snobot.simulator.module_wrapper.ASensorWrapper;

public class AnalogGyroWrapper extends ASensorWrapper implements IGyroWrapper
{

    protected final int mPort;
    protected double mAngle;

    public AnalogGyroWrapper(int aPort, String name)
    {
        super(name);
        mPort = aPort;
    }

    public void setAngle(double aAngle)
    {
        boolean isUpdate = mAngle != aAngle;
        mAngle = aAngle;
        if (isUpdate)
        {
            SensorFeedbackJni.setAnalogGyroAngle(mPort, aAngle);
        }
    }

    public double getAngle()
    {
        return mAngle;
    }
}
