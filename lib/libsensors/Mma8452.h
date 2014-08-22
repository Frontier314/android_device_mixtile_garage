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

#ifndef ANDROID_MMA8452_SENSOR_H
#define ANDROID_MMA8452_SENSOR_H

#include <stdint.h>
#include <errno.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include "sensors.h"
#include "SamsungSensorBase.h"
#include "InputEventReader.h"

// 1024 LSG = 1G
#define LSG                         (1024.0f)
#define NUMOFACCDATA                (8.0f)
//#define RANGE_A                     (2*GRAVITY_EARTH)
#define RANGE_A                     (8192)
#define CONVERT_A                   (GRAVITY_EARTH / LSG)
#define CONVERT_A_X                 (CONVERT_A)
#define CONVERT_A_Y                 (CONVERT_A)
#define CONVERT_A_Z                 (CONVERT_A)

/*****************************************************************************/


struct mma8452acc_t {
		short x,
			  y,
			  z;
} ;

/* smb ioctl command label */
//#define IOCTL_SMB_GET_ACC_VALUE		0
//#define DCM_IOC_MAGIC			's'
//#define IOC_SET_ACCELEROMETER	_IO (DCM_IOC_MAGIC, 0x64)
//#define BMA150_CALIBRATION		_IOWR(DCM_IOC_MAGIC,48,short)

#define SMB_POWER_OFF               0
#define SMB_POWER_ON                1

struct input_event;

class Mma8452Sensor : public SamsungSensorBase {
    char input_sysfs_path[PATH_MAX];
    int input_sysfs_path_len;

public:
            Mma8452Sensor();
    virtual ~Mma8452Sensor();
    virtual int readEvents(sensors_event_t* data, int count);
    virtual bool hasPendingEvents() const;
    virtual int setDelay(int32_t handle, int64_t ns);
    virtual int enable(int32_t handle, int enabled);
};


/*****************************************************************************/

#endif  // ANDROID_MMA8452_SENSOR_H
