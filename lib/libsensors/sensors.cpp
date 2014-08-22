/*
 * Copyright (C) 2011 The Android Open-Source Project
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

#define LOG_NDEBUG 0
#define LOG_TAG "Sensors"
//#define FUNC_LOG ALOGV("%s", __PRETTY_FUNCTION__)
#define FUNC_LOG

#include <hardware/sensors.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <math.h>
#include <poll.h>
#include <pthread.h>
#include <stdlib.h>

#include <linux/input.h>

#include <utils/Atomic.h>
#include <utils/Log.h>

#include "sensors.h"

//#include "MPLSensor.h"
//#include "LightSensor.h"
//#include "PressureSensor.h"
//Apollo +
#include "Mma8452.h"
//Apollo -
#include "GyroscopeSensor.h"
#include "CompassSensor.h"
#include "LightSensor.h"
#include "ProximitySensor.h"

/*****************************************************************************/

#define DELAY_OUT_TIME 0x7FFFFFFF

#define LIGHT_SENSOR_POLLTIME    2000000000

#define SENSORS_ROTATION_VECTOR  (1<<ID_RV)
#define SENSORS_LINEAR_ACCEL     (1<<ID_LA)
#define SENSORS_GRAVITY          (1<<ID_GR)
#define SENSORS_GYROSCOPE        (1<<ID_GY)
#define SENSORS_ACCELERATION     (1<<ID_A)
#define SENSORS_MAGNETIC_FIELD   (1<<ID_M)
#define SENSORS_ORIENTATION      (1<<ID_O)
#define SENSORS_LIGHT            (1<<ID_L)
#define SENSORS_PROXIMITY        (1<<ID_P)
#define SENSORS_PRESSURE         (1<<ID_PR)

#define SENSORS_ROTATION_VECTOR_HANDLE  (ID_RV)
#define SENSORS_LINEAR_ACCEL_HANDLE     (ID_LA)
#define SENSORS_GRAVITY_HANDLE          (ID_GR)
#define SENSORS_GYROSCOPE_HANDLE        (ID_GY)
#define SENSORS_ACCELERATION_HANDLE     (ID_A)
#define SENSORS_MAGNETIC_FIELD_HANDLE   (ID_M)
#define SENSORS_ORIENTATION_HANDLE      (ID_O)
#define SENSORS_LIGHT_HANDLE            (ID_L)
#define SENSORS_PROXIMITY_HANDLE        (ID_P)
#define SENSORS_PRESSURE_HANDLE         (ID_PR)
#define AKM_FTRACE 0
#define AKM_DEBUG 0
#define AKM_DATA 0

/*****************************************************************************/

/* The SENSORS Module */
//Apollo +
//#define LOCAL_SENSORS (3)
#define LOCAL_SENSORS (2)
//Apollo -
static const struct sensor_t sSensorList[] = {
    { "MMA8452 3-axis Accelerometer", // name
        "Freescale",                    // vendor
        1,                              // version
        SENSORS_ACCELERATION_HANDLE,    // handle
        SENSOR_TYPE_ACCELEROMETER,      // type
        RANGE_A,                        // maxRange
        CONVERT_A,                      // resolution
        0.23f,                          // power
        20000,                          // minDelay
        0				// fifoReservedEventCount
    },
    { "L3G4200D Gyroscope", 
      "ST",
	1,
      SENSORS_GYROSCOPE_HANDLE,
      SENSOR_TYPE_GYROSCOPE,
      2000.0f, 
      1.0f, 
      0.5f, 
      10000, 
      0
     },
    { "MMC3280 Magnetic field sensor",
      "MEMSIC ",
      1, 
      SENSORS_MAGNETIC_FIELD_HANDLE,
      SENSOR_TYPE_MAGNETIC_FIELD, 
      2000.0f, 
      CONVERT_M, 
      6.8f, 
      10000, 
      0
     },
    { "BH1750 Light sensor",
      "Rohm",
       1, 
       SENSORS_LIGHT_HANDLE,
       SENSOR_TYPE_LIGHT, 
       10240.0f, 
       1.0f, 
       0.75f, 
       0, 
       0
    },
    { "APDS-9900 Proximity sensor",
      "Avago",
      1, 
      SENSORS_PROXIMITY_HANDLE,
      SENSOR_TYPE_PROXIMITY, 
      100.0f, 
      1.0f, 
      0.75f, 
      0, 
      0
    },          
};

static int numSensors = LOCAL_SENSORS;

static int open_sensors(const struct hw_module_t* module, const char* id,
                        struct hw_device_t** device);


static int sensors__get_sensors_list(struct sensors_module_t* module,
                                     struct sensor_t const** list)
{
    *list = sSensorList;
//    return numSensors;
    return ARRAY_SIZE(sSensorList);
}

static struct hw_module_methods_t sensors_module_methods = {
        open: open_sensors
};

struct sensors_module_t HAL_MODULE_INFO_SYM = {
        common: {
                tag: HARDWARE_MODULE_TAG,
                version_major: 1,
                version_minor: 0,
                id: SENSORS_HARDWARE_MODULE_ID,
                name: "Samsung Sensor module",
                author: "Samsung Electronic Company",
                methods: &sensors_module_methods,
                dso: 0,
                reserved: {},
        },
        get_sensors_list: sensors__get_sensors_list,
};

struct sensors_poll_context_t {
    struct sensors_poll_device_t device; // must be first

        sensors_poll_context_t();
        ~sensors_poll_context_t();
    int activate(int handle, int enabled);
    int setDelay(int handle, int64_t ns);
    int pollEvents(sensors_event_t* data, int count);

private:
    enum {
//        mpl               = 0,  //all mpl entries must be consecutive and in this order
//        mpl_accel,
//        mpl_timer,
//        light,
//        proximity,
//        pressure,
//Apollo +
        mma8452 = 0,
//Apollo -
				gyroscope,
				mmc3280,
				light,
				proximity,
        numSensorDrivers,       // wake pipe goes here
//        mpl_power,              //special handle for MPL pm interaction
        numFds,
    };

    static const size_t wake = numFds - 1;
    static const char WAKE_MESSAGE = 'W';
    struct pollfd mPollFds[numFds];
    int mWritePipeFd;
    SensorBase* mSensors[numSensorDrivers];

    int handleToDriver(int handle) const {
        switch (handle) {
            case ID_A:
                return mma8452;
            case ID_GY:    
            		return gyroscope;
            case ID_M:
            		return mmc3280;
						case ID_L:
                return light;
           	case ID_P:
                return proximity;                 				
        }
        return -EINVAL;
    }
};

/*****************************************************************************/

sensors_poll_context_t::sensors_poll_context_t()
{
//    FUNC_LOG;
//    MPLSensor* p_mplsen = new MPLSensor();
//    setCallbackObject(p_mplsen); //setup the callback object for handing mpl callbacks
//    numSensors =
//        LOCAL_SENSORS +
//        p_mplsen->populateSensorList(sSensorList + LOCAL_SENSORS,
//                                     sizeof(sSensorList[0]) * (ARRAY_SIZE(sSensorList) - LOCAL_SENSORS));
//

//Apollo +
    mSensors[mma8452] = new Mma8452Sensor();
    mPollFds[mma8452].fd = mSensors[mma8452]->getFd();
    mPollFds[mma8452].events = POLLIN;
    mPollFds[mma8452].revents = 0;
//Apollo -

    mSensors[gyroscope] = new GyroscopeSensor();
    mPollFds[gyroscope].fd = mSensors[gyroscope]->getFd();
    mPollFds[gyroscope].events = POLLIN;
    mPollFds[gyroscope].revents = 0;
    
    mSensors[mmc3280] = new CompassSensor();
    mPollFds[mmc3280].fd = mSensors[mmc3280]->getFd();
    mPollFds[mmc3280].events = POLLIN;
    mPollFds[mmc3280].revents = 0;

    mSensors[light] = new LightSensor();
    mPollFds[light].fd = mSensors[light]->getFd();
    mPollFds[light].events = POLLIN;
    mPollFds[light].revents = 0;   
    
    mSensors[proximity] = new ProximitySensor();
    mPollFds[proximity].fd = mSensors[proximity]->getFd();
    mPollFds[proximity].events = POLLIN;
    mPollFds[proximity].revents = 0; 
    
    int wakeFds[2];
    int result = pipe(wakeFds);
    ALOGE_IF(result<0, "error creating wake pipe (%s)", strerror(errno));
    fcntl(wakeFds[0], F_SETFL, O_NONBLOCK);
    fcntl(wakeFds[1], F_SETFL, O_NONBLOCK);
    mWritePipeFd = wakeFds[1];

    mPollFds[wake].fd = wakeFds[0];
    mPollFds[wake].events = POLLIN;
    mPollFds[wake].revents = 0;

//    //setup MPL pm interaction handle
//    mPollFds[mpl_power].fd = ((MPLSensor*)mSensors[mpl])->getPowerFd();
//    mPollFds[mpl_power].events = POLLIN;
//    mPollFds[mpl_power].revents = 0;
}

sensors_poll_context_t::~sensors_poll_context_t()
{
    FUNC_LOG;
    for (int i=0 ; i<numSensorDrivers ; i++) {
        delete mSensors[i];
    }
    close(mPollFds[wake].fd);
    close(mWritePipeFd);
}

int sensors_poll_context_t::activate(int handle, int enabled)
{
    FUNC_LOG;
    int index = handleToDriver(handle);
    if (index < 0) return index;
    int err =  mSensors[index]->enable(handle, enabled);
    if (!err) {
        const char wakeMessage(WAKE_MESSAGE);
        int result = write(mWritePipeFd, &wakeMessage, 1);
        ALOGE_IF(result<0, "error sending wake message (%s)", strerror(errno));
    }
    return err;
}

int sensors_poll_context_t::setDelay(int handle, int64_t ns)
{
    FUNC_LOG;
    int index = handleToDriver(handle);
    if (index < 0) return index;
    return mSensors[index]->setDelay(handle, ns);
}

int sensors_poll_context_t::pollEvents(sensors_event_t* data, int count)
{
    //FUNC_LOG;
    int nbEvents = 0;
    int n = 0;
    int polltime = -1;

    do {
        // see if we have some leftover from the last poll()
        for (int i=0 ; count && i<numSensorDrivers ; i++) {
            SensorBase* const sensor(mSensors[i]);
            if ((mPollFds[i].revents & POLLIN) || (sensor->hasPendingEvents())) {
                int nb = sensor->readEvents(data, count);
                if (nb < count) {
                    // no more data for this sensor
                    mPollFds[i].revents = 0;
                }
                count -= nb;
                nbEvents += nb;
                data += nb;

//                //special handling for the mpl, which has multiple handles
//                if(i==mpl) {
//                    i+=2; //skip accel and timer
//                    mPollFds[mpl_accel].revents = 0;
//                    mPollFds[mpl_timer].revents = 0;
//                }
//                if(i==mpl_accel) {
//                    i+=1; //skip timer
//                    mPollFds[mpl_timer].revents = 0;
//                }
            }
        }

        if (count) {
            // we still have some room, so try to see if we can get
            // some events immediately or just wait if we don't have
            // anything to return
            int i;

            do {
                n = poll(mPollFds, numFds, nbEvents ? 0 : polltime);
            } while (n < 0 && errno == EINTR);
            if (n<0) {
                ALOGE("poll() failed (%s)", strerror(errno));
                return -errno;
            }
            if (mPollFds[wake].revents & POLLIN) {
                char msg;
                int result = read(mPollFds[wake].fd, &msg, 1);
                ALOGE_IF(result<0, "error reading from wake pipe (%s)", strerror(errno));
                ALOGE_IF(msg != WAKE_MESSAGE, "unknown message on wake queue (0x%02x)", int(msg));
                mPollFds[wake].revents = 0;
            }
//            if(mPollFds[mpl_power].revents & POLLIN) {
//                ((MPLSensor*)mSensors[mpl])->handlePowerEvent();
//                mPollFds[mpl_power].revents = 0;
//            }
        }
        // if we have events and space, go read them
    } while (n && count);

    return nbEvents;
}

/*****************************************************************************/

static int poll__close(struct hw_device_t *dev)
{
    FUNC_LOG;
    sensors_poll_context_t *ctx = (sensors_poll_context_t *)dev;
    if (ctx) {
        delete ctx;
    }
    return 0;
}

static int poll__activate(struct sensors_poll_device_t *dev,
                          int handle, int enabled)
{
    FUNC_LOG;
    sensors_poll_context_t *ctx = (sensors_poll_context_t *)dev;
    return ctx->activate(handle, enabled);
}

static int poll__setDelay(struct sensors_poll_device_t *dev,
                          int handle, int64_t ns)
{
    FUNC_LOG;
    sensors_poll_context_t *ctx = (sensors_poll_context_t *)dev;
    return ctx->setDelay(handle, ns);
}

static int poll__poll(struct sensors_poll_device_t *dev,
                      sensors_event_t* data, int count)
{
    FUNC_LOG;
    sensors_poll_context_t *ctx = (sensors_poll_context_t *)dev;
    return ctx->pollEvents(data, count);
}

/*****************************************************************************/

/** Open a new instance of a sensor device using name */
static int open_sensors(const struct hw_module_t* module, const char* id,
                        struct hw_device_t** device)
{
    FUNC_LOG;
    int status = -EINVAL;
    sensors_poll_context_t *dev = new sensors_poll_context_t();

    memset(&dev->device, 0, sizeof(sensors_poll_device_t));

    dev->device.common.tag = HARDWARE_DEVICE_TAG;
    dev->device.common.version  = 0;
    dev->device.common.module   = const_cast<hw_module_t*>(module);
    dev->device.common.close    = poll__close;
    dev->device.activate        = poll__activate;
    dev->device.setDelay        = poll__setDelay;
    dev->device.poll            = poll__poll;

    *device = &dev->device.common;
    status = 0;

    return status;
}


