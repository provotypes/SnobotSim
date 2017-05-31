
#include <assert.h>
#include <jni.h>
#include "support/jni_util.h"

#include "com_snobot_simulator_module_wrapper_EncoderWrapperJni.h"
#include "SnobotSim/SensorActuatorRegistry.h"
#include "SnobotSim/PortUnwrapper.h"
#include <sstream>

using namespace wpi::java;

extern "C"
{
/*
 * Class:     com_snobot_simulator_module_wrapper_EncoderWrapperJni
 * Method:    getHandle
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_com_snobot_simulator_module_1wrapper_EncoderWrapperJni_getHandle
  (JNIEnv *, jclass, jint handleA, jint handleB)
{
    int basicHandle = (handleA << 8) + handleB;
    std::shared_ptr<EncoderWrapper> wrapper = SensorActuatorRegistry::Get().GetEncoderWrapper(basicHandle, false);
    if(wrapper)
    {
        return basicHandle;
    }

    int packedHandle = (WrapPort(handleA) << 8) + WrapPort(handleB);
    wrapper = SensorActuatorRegistry::Get().GetEncoderWrapper(packedHandle, false);
    if(wrapper)
    {
        return packedHandle;
    }

    std::cerr << "Could not find encoder with ports (" << handleA << ", " << handleB << "), tried " << basicHandle << " and " << packedHandle << std::endl;

    return -1;

}

/*
 * Class:     com_snobot_simulator_module_wrapper_EncoderWrapperJni
 * Method:    setName
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_snobot_simulator_module_1wrapper_EncoderWrapperJni_setName
  (JNIEnv * env, jclass, jint aPortHandle, jstring aName)
{
    std::shared_ptr<EncoderWrapper> wrapper = SensorActuatorRegistry::Get().GetEncoderWrapper(aPortHandle);
    if(wrapper)
    {
        wrapper->SetName(env->GetStringUTFChars(aName, NULL));
    }
}

/*
 * Class:     com_snobot_simulator_module_wrapper_EncoderWrapperJni
 * Method:    getName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_snobot_simulator_module_1wrapper_EncoderWrapperJni_getName(JNIEnv * env, jclass, jint portHandle)
{
    jstring output = MakeJString(env, SensorActuatorRegistry::Get().GetEncoderWrapper(portHandle)->GetName());

    return output;
}

/*
 * Class:     com_snobot_simulator_module_wrapper_EncoderWrapperJni
 * Method:    getWantsHidden
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_snobot_simulator_module_1wrapper_EncoderWrapperJni_getWantsHidden(JNIEnv *, jclass, jint portHandle)
{
    return SensorActuatorRegistry::Get().GetEncoderWrapper(portHandle)->WantsHidden();
}

/*
 * Class:     com_snobot_simulator_module_wrapper_EncoderWrapperJni
 * Method:    isConnected
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_snobot_simulator_module_1wrapper_EncoderWrapperJni_isHookedUp(JNIEnv *, jclass, jint portHandle)
{
    return SensorActuatorRegistry::Get().GetEncoderWrapper(portHandle)->IsHookedUp();
}

/*
 * Class:     com_snobot_simulator_module_wrapper_EncoderWrapperJni
 * Method:    getRaw
 * Signature: (I)D
 */
JNIEXPORT jdouble JNICALL Java_com_snobot_simulator_module_1wrapper_EncoderWrapperJni_getRaw(JNIEnv *, jclass, jint portHandle)
{
    return SensorActuatorRegistry::Get().GetEncoderWrapper(portHandle)->GetRaw();
}

/*
 * Class:     com_snobot_simulator_module_wrapper_EncoderWrapperJni
 * Method:    getVoltagePercentage
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_com_snobot_simulator_module_1wrapper_EncoderWrapperJni_getDistance(JNIEnv *, jclass, jint portHandle)
{
    return SensorActuatorRegistry::Get().GetEncoderWrapper(portHandle)->GetDistance();
}

/*
 * Class:     com_snobot_simulator_module_wrapper_EncoderWrapperJni
 * Method:    getPortList
 * Signature: ()[I
 */
JNIEXPORT jintArray JNICALL Java_com_snobot_simulator_module_1wrapper_EncoderWrapperJni_getPortList(JNIEnv * env, jclass)
{
    const std::map<int, std::shared_ptr<EncoderWrapper>>& encoders = SensorActuatorRegistry::Get().GetEncoderWrapperMap();

    jintArray output = env->NewIntArray(encoders.size());

    jint values[30];

    std::map<int, std::shared_ptr<EncoderWrapper>>::const_iterator iter = encoders.begin();

    int ctr = 0;
    for (; iter != encoders.end(); ++iter)
    {
        values[ctr++] = iter->first;
    }

    env->SetIntArrayRegion(output, 0, encoders.size(), values);

    return output;
}


}