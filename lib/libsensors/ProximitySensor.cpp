/*
 * Copyright (C) 2011 Samsung
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
#include <pthread.h>

#include <cutils/log.h>

#include "ProximitySensor.h"

/*****************************************************************************/

ProximitySensor::ProximitySensor()
    : SamsungSensorBase(NULL, "apds9900", ABS_MISC)
{
    mPendingEvent.version = sizeof(sensors_event_t);
    mPendingEvent.sensor = ID_P;
    mPendingEvent.type = SENSOR_TYPE_PROXIMITY;
    memset(mPendingEvent.data, 0, sizeof(mPendingEvent.data));

    if (data_fd) {
        strcpy(input_sysfs_path, "/sys/class/input/");
        strcat(input_sysfs_path, input_name);
        strcat(input_sysfs_path, "/device/");
        input_sysfs_path_len = strlen(input_sysfs_path);
      //  enable(0, 1);
    }
}

ProximitySensor::~ProximitySensor() {
    if (mEnabled) {
        enable(0, 0);
    }
}

int ProximitySensor::setDelay(int32_t handle, int64_t ns)
{
    int fd;
//    strcpy(&input_sysfs_path[input_sysfs_path_len], "poll_delay");
//    fd = open(input_sysfs_path, O_RDWR);
//    if (fd >= 0) {
//        char buf[80];
//        sprintf(buf, "%lld", ns);
//        write(fd, buf, strlen(buf)+1);
//        close(fd);
//        return 0;
//    }
    return 0;
}

int ProximitySensor::enable(int32_t handle, int en)
{
//    int flags = en ? 1 : 0;
//    if (flags != mEnabled) {
//        int fd;
//        strcpy(&input_sysfs_path[input_sysfs_path_len], "enable");
//        fd = open(input_sysfs_path, O_RDWR);
//        if (fd >= 0) {
//            char buf[2];
//            int err;
//            buf[1] = 0;
//            if (flags) {
//                buf[0] = '1';
//            } else {
//                buf[0] = '0';
//            }
//            err = write(fd, buf, sizeof(buf));
//            close(fd);
//            mEnabled = flags;
//            return 0;
//        }
//        return -1;
//    }
    return 0;
}
bool ProximitySensor::hasPendingEvents() const {
    /* FIXME probably here should be returning mEnabled but instead
	mHasPendingEvents. It does not work, so we cheat.*/
    //AALOGE("CompassSensor::~hasPendingEvents %d", mHasPendingEvent ? 1 : 0 );
    return mHasPendingEvent;
}

int ProximitySensor::readEvents(sensors_event_t* data, int count)
{
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

    while (count && mInputReader.readEvent(data_fd,&event)) {
        int type = event->type;
        if (type == EV_REL) {
            if (event->code == ABS_X) {
							mPendingEvent.distance = event->value;
//							ALOGE("ProximitySensor: Distance = %f ++++++++++++",mPendingEvent.distance);
            }
//            else if(event->code == ABS_Y){
//            		mPendingEvent.light = event->value;
////            	ALOGE("ProximitySensor: light = %f ++++++++++++",mPendingEvent.light);	
//            }
        } else if (type == EV_SYN) {
            mPendingEvent.timestamp = timevalToNano(event->time);
            if (mEnabled) {
                *data++ = mPendingEvent;
                count--;
                numEventReceived++;
            }
        } else {
            ALOGE("ProximitySensor: unknown event (type=%d, code=%d)",
                    type, event->code);
        }
        mInputReader.next();
    }
 
  pthread_mutex_unlock(&mLock);
	return numEventReceived++;
		 
}
