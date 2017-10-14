package com.snobot.simulator.simulator_components.navx;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import com.snobot.simulator.SensorActuatorRegistry;
import com.snobot.simulator.module_wrapper.ASensorWrapper;
import com.snobot.simulator.simulator_components.gyro.IGyroWrapper;

public class NavxSimulator
{
    private class NavxGyro extends ASensorWrapper implements IGyroWrapper
    {

        public NavxGyro(String aName)
        {
            super(aName);
        }

        @Override
        public double getAngle()
        {
            // TODO Auto-generated method stub
            return 0;
        }

        @Override
        public void setAngle(double aAngle)
        {
            // TODO Auto-generated method stub

        }

    }

    protected static int TIMESTAMP = 1;

    protected final IGyroWrapper mYawGyro;
    protected final IGyroWrapper mPitchGyro;
    protected final IGyroWrapper mRollGyro;
    protected final int mNativePort;

    public NavxSimulator(int aNativePort, int aSimulatorOffset)
    {
        mYawGyro = new NavxGyro("NavX Pitch");
        mPitchGyro = new NavxGyro("NavX Yaw");
        mRollGyro = new NavxGyro("NavX Roll");

        mNativePort = aNativePort;

        int basePort = aSimulatorOffset + aNativePort * 3;

        SensorActuatorRegistry.get().register(mYawGyro, basePort + 0);
        SensorActuatorRegistry.get().register(mPitchGyro, basePort + 1);
        SensorActuatorRegistry.get().register(mRollGyro, basePort + 2);
    }

    protected ByteBuffer createConfigBuffer()
    {
        ByteBuffer output = ByteBuffer.allocateDirect(17);

        output.put((byte) 1);
        output.put((byte) 2);
        output.put((byte) 3);
        output.put((byte) 4);
        output.put((byte) 5);
        output.putShort((short) 0x0607);
        output.put((byte) 6);
        output.put((byte) 7);
        output.put((byte) 10);
        output.putShort((short) 0xDEAD);
        output.putInt(5);
        // output.putShort((short) 0xBEEF);

        return output;
    }

    protected ByteBuffer createDataBuffer(int aFirstAddress)
    {
        ByteBuffer output = ByteBuffer.allocateDirect(86 - aFirstAddress);

        output.order(ByteOrder.LITTLE_ENDIAN);
        output.putInt(0x12 - aFirstAddress, TIMESTAMP);
        ++TIMESTAMP;

        output.put(0x08 - aFirstAddress, (byte) 1); // Op Status
        output.put(0x0A - aFirstAddress, (byte) 2); // Self Test
        output.put(0x09 - aFirstAddress, (byte) 3); // Cal Status
        output.put(0x10 - aFirstAddress, (byte) 4); // Sensor Status
        output.put(0x04 - aFirstAddress, (byte) 60); // Update Rate

        output.putShort(0x16 - aFirstAddress, (short) (boundBetweenNeg180Pos180(mYawGyro.getAngle()) * 100)); // Yaw
        output.putShort(0x1A - aFirstAddress, (short) (boundBetweenNeg180Pos180(mPitchGyro.getAngle()) * 100)); // Pitch
        output.putShort(0x18 - aFirstAddress, (short) (boundBetweenNeg180Pos180(mRollGyro.getAngle()) * 100)); // Roll
        output.putShort(0x1C - aFirstAddress, (short) (0 * 100)); // Heading
        output.putShort(0x32 - aFirstAddress, (short) (0 * 100)); // Temperature
        output.putShort(0x24 - aFirstAddress, (short) (0 * 1000)); // Linear
                                                                   // Accel X
        output.putShort(0x26 - aFirstAddress, (short) (0 * 1000)); // Linear
                                                                   // Accel Y
        output.putShort(0x28 - aFirstAddress, (short) (0 * 1000)); // Linear
                                                                   // Accel Z

        return output;
    }

    private double boundBetweenNeg180Pos180(double input)
    {
        double output = input;
        while (output > 180)
        {
            output -= 360;
        }
        while (output < -180)
        {
            output += 360;
        }

        return output;
    }
}
