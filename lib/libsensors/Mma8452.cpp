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


#include "Mma8452.h"
/*****************************************************************************/
Mma8452Sensor::Mma8452Sensor()
    : SamsungSensorBase(NULL, "mma8452", ABS_MISC)

{
    ALOGD("Mma8452Sensor::Mma8452Sensor()");
    mPendingEvent.version = sizeof(sensors_event_t);
    mPendingEvent.sensor = ID_A;
    mPendingEvent.type = SENSOR_TYPE_ACCELEROMETER;
    memset(mPendingEvent.data, 0, sizeof(mPendingEvent.data));
    
    ALOGD("Mma8452Sensor::Mma8452Sensor() open data_fd");
	
    if (data_fd) {
        strcpy(input_sysfs_path, "/sys/class/input/");
        strcat(input_sysfs_path, input_name);
        strcat(input_sysfs_path, "/device/");
        input_sysfs_path_len = strlen(input_sysfs_path);

        enable(0, 1);
    }
}

Mma8452Sensor::~Mma8452Sensor() {

    ALOGD("Mma8452Sensor::~Mma8452Sensor()");
    if (mEnabled) {
        enable(0, 0);
    }
}


int Mma8452Sensor::enable(int32_t, int en) {

	   
    ALOGD("Mma8452Sensor:: enable(0, %d)", en);
    int flags = en ? 1 : 0;
    if (flags != mEnabled) {
        strcpy(&input_sysfs_path[input_sysfs_path_len], "enable");
        mEnabled = flags;
    }
    return 0;
}


bool Mma8452Sensor::hasPendingEvents() const {
    /* FIXME probably here should be returning mEnabled but instead mHasPendingEvents. It does not work, so we cheat.*/
    //ALOGD("Mma8452Sensor::~hasPendingEvents %d", mHasPendingEvent ? 1 : 0 );
    return mHasPendingEvent;
}


int Mma8452Sensor::setDelay(int32_t handle, int64_t ns)
{
//    ALOGD("Mma8452Sensor:: setDelay(%d, %ld)", handle, ns);
    /* FIXME needs changes to the kernel driver.
       We need to add a IOCTL that can set the samplingrate
       the driver in ther kernel supports this allready only need
       to add a IOCTL on both sides for that*/
    return 0;
}


int Mma8452Sensor::readEvents(sensors_event_t* data, int count)
{
    //ALOGD("Mma8452Sensor::~readEvents() %d", count);
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
        if (type == EV_ABS) {
            float value = event->value;
            if (event->code == REL_X) {
                mPendingEvent.acceleration.x = value * CONVERT_A;
            } else if (event->code == REL_Y) {
                mPendingEvent.acceleration.y = value * CONVERT_A;
            } else if (event->code == REL_Z) {
                mPendingEvent.acceleration.z = value * (-CONVERT_A);
            }
        } else if (type == EV_SYN) {
//ALOGD("x=%f y=%f z=%f\n", mPendingEvent.acceleration.x, mPendingEvent.acceleration.y, mPendingEvent.acceleration.z);
            mPendingEvent.timestamp = timevalToNano(event->time);
            if (mEnabled) {
                *data++ = mPendingEvent;
                count--;
                numEventReceived++;
            }
        } else {
            ALOGE("Mma8452Sensor: unknown event (type=%d, code=%d)",
                    type, event->code);
        }
        mInputReader.next();
    }
 
	//ALOGD("Mma8452Sensor::~readEvents() numEventReceived = %d", numEventReceived);
  pthread_mutex_unlock(&mLock);
	return numEventReceived++;
		
}
