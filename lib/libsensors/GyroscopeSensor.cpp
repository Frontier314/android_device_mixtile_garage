/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <poll.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/select.h>
#include <cutils/log.h>

#include "GyroscopeSensor.h"
/*****************************************************************************/
GyroscopeSensor::GyroscopeSensor()
    : SamsungSensorBase(NULL, "l3g4200d", ABS_MISC)

{
    ALOGD("GyroscopeSensor::GyroscopeSensor()");
    mPendingEvent.version = sizeof(sensors_event_t);
    mPendingEvent.sensor = ID_GY;
    mPendingEvent.type = SENSOR_TYPE_GYROSCOPE;
    memset(mPendingEvent.data, 0, sizeof(mPendingEvent.data));
    
    ALOGD("GyroscopeSensor::GyroscopeSensor() open data_fd");
	
    if (data_fd) {
        strcpy(input_sysfs_path, "/sys/class/input/");
        strcat(input_sysfs_path, input_name);
        strcat(input_sysfs_path, "/device/");
        input_sysfs_path_len = strlen(input_sysfs_path);

        enable(0, 1);
    }
}

GyroscopeSensor::~GyroscopeSensor() {

    ALOGD("GyroscopeSensor::~GyroscopeSensor()");
    if (mEnabled) {
        enable(0, 0);
    }
}


int GyroscopeSensor::enable(int32_t, int en) {

	   
//    ALOGD("GyroscopeSensor:: enable(0, %d)", en);
//    int flags = en ? 1 : 0;
//    if (flags != mEnabled) {
//        strcpy(&input_sysfs_path[input_sysfs_path_len], "enable");
//        mEnabled = flags;
//    }
    return 0;
}


bool GyroscopeSensor::hasPendingEvents() const {
    /* FIXME probably here should be returning mEnabled but instead mHasPendingEvents. It does not work, so we cheat.*/
    //ALOGD("GyroscopeSensor::~hasPendingEvents %d", mHasPendingEvent ? 1 : 0 );
    return mHasPendingEvent;
}


int GyroscopeSensor::setDelay(int32_t handle, int64_t ns)
{
//    ALOGD("GyroscopeSensor:: setDelay(%d, %ld)", handle, ns);
    /* FIXME needs changes to the kernel driver.
       We need to add a IOCTL that can set the samplingrate
       the driver in ther kernel supports this allready only need
       to add a IOCTL on both sides for that*/
    return 0;
}


int GyroscopeSensor::readEvents(sensors_event_t* data, int count)
{
    //ALOGD("GyroscopeSensor::~readEvents() %d", count);
    if (count < 1)
        return -EINVAL;
        
    pthread_mutex_lock(&mLock);
    if (mHasPendingEvent) {
        mHasPendingEvent = false;
        mPendingEvent.timestamp = getTimestamp();
        *data = mPendingEvent;
        return mEnabled ? 1 : 0;
    }
        
//    ssize_t n = mInputReader.fill(data_fd);
//    if (n < 0)
//        return n;

    int numEventReceived = 0;
    input_event const* event;
	
    while (count && mInputReader.readEvent(data_fd, &event)) {
        int type = event->type;
        if (type == EV_REL) {
            float value = event->value;
            if (event->code == REL_RX) {
                mPendingEvent.gyro.x = value* CONVERT_GYRO_X ;
            } else if (event->code == REL_RY) {
                mPendingEvent.gyro.y = value* CONVERT_GYRO_Y ;
            } else if (event->code == REL_RZ) {
                mPendingEvent.gyro.z = value* CONVERT_GYRO_Z ;
            }
        } else if (type == EV_SYN) {
//      ALOGD("x=%f y=%f z=%f\n", mPendingEvent.gyro.x, mPendingEvent.gyro.y, mPendingEvent.gyro.z);
//            mPendingEvent.timestamp = timevalToNano(event->time);
            if (mEnabled) {
                *data++ = mPendingEvent;
                count--;
                numEventReceived++;
            }
        } else {
            ALOGE("GyroscopeSensor: unknown event (type=%d, code=%d)",
                    type, event->code);
        }
        mInputReader.next();
    }
 
	//ALOGD("GyroscopeSensor::~readEvents() numEventReceived = %d", numEventReceived);
  pthread_mutex_unlock(&mLock);
	return numEventReceived++;
		
}
