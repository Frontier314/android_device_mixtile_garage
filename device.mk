# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


# This file is the device-specific product definition file for
# garage. It lists all the overlays, files, modules and properties
# that are specific to this hardware: i.e. those are device-specific
# drivers, configuration files, settings, etc...

# These is the hardware-specific overlay, which points to the location
# of hardware-specific resource overrides, typically the frameworks and
# application settings that are stored in resourced.

LOCAL_PATH := device/mixtile/garage

#TARGET_DEVICE = mixtile_garage

include $(LOCAL_PATH)/BoardConfig.mk

# These are for the multi-storage mount.
source_vold_fstab_file := $(LOCAL_PATH)/conf/vold.fstab
PRODUCT_COPY_FILES += $(source_vold_fstab_file):system/etc/vold.fstab

DEVICE_PACKAGE_OVERLAYS := $(LOCAL_PATH)/overlay

ifeq ($(BOARD_USES_HGL),true)
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/conf/egl.cfg:system/lib/egl/egl.cfg \
	hardware/samsung_slsi/exynos4/lib/mali_ump/libEGL_mali.so:system/lib/egl/libEGL_mali.so \
	hardware/samsung_slsi/exynos4/lib/mali_ump/libGLESv1_CM_mali.so:system/lib/egl/libGLESv1_CM_mali.so \
	hardware/samsung_slsi/exynos4/lib/mali_ump/libGLESv2_mali.so:system/lib/egl/libGLESv2_mali.so \
	hardware/samsung_slsi/exynos4/lib/mali_ump/libMali.so:system/lib/libMali.so \
	hardware/samsung_slsi/exynos4/lib/mali_ump/libMali.so:obj/lib/libMali.so \
	hardware/samsung_slsi/exynos4/lib/mali_ump/libUMP.so:system/lib/libUMP.so \
	hardware/samsung_slsi/exynos4/lib/mali_ump/libUMP.so:obj/lib/libUMP.so \
	hardware/samsung_slsi/exynos4/lib/mali_ump/libion.so:system/lib/libion.so \
	hardware/samsung_slsi/exynos4/lib/mali_ump/libion.so:obj/lib/libion.so		
endif

# Init files
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/conf/init.garage.rc:root/init.garage.rc \
	$(LOCAL_PATH)/conf/init.garage.usb.rc:root/init.garage.usb.rc

# For V4L2
ifeq ($(BOARD_USE_V4L2), true)
ifeq ($(BOARD_USE_V4L2_ION), true)
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/conf/ueventd.garage.v4l2ion.rc:root/ueventd.garage.rc
else
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/conf/ueventd.garage.v4l2.rc:root/ueventd.garage.rc
endif
else
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/conf/ueventd.garage.rc:root/ueventd.garage.rc
endif

# Prebuilt kl keymaps
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/samsung-keypad.kl:system/usr/keylayout/samsung-keypad.kl \
	$(LOCAL_PATH)/pixcir-i2c-ts_key.kl:system/usr/keylayout/pixcir-i2c-ts_key.kl

# Generated kcm keymaps
PRODUCT_PACKAGES := \
	samsung-keypad.kcm

# Filesystem management tools
PRODUCT_PACKAGES += \
	make_ext4fs \
	setup_fs

# audio
PRODUCT_PACKAGES += \
	audio_policy.$(TARGET_PRODUCT) \
	audio.primary.$(TARGET_PRODUCT) \
	audio.a2dp.default \
	libaudioutils \
	tinyplay \
	tinycap \
	tinymix

# ULP Audio
ifeq ($(USE_ULP_AUDIO),true)
PRODUCT_PACKAGES += \
	libaudiohw \
	MusicULP \
	libsa_jni
endif

# ALP Audio
ifeq ($(BOARD_USE_ALP_AUDIO),true)
PRODUCT_PACKAGES += \
	libOMX.SEC.MP3.Decoder
endif

# Camera
PRODUCT_PACKAGES += \
	camera.$(TARGET_PRODUCT)

# gralloc add by bbk for user mode
PRODUCT_PACKAGES += \
	gralloc.$(TARGET_PRODUCT)

# gps
PRODUCT_PACKAGES += \
	gps.$(TARGET_PRODUCT)

# SEC_Camera
ifeq ($(USE_SEC_CAMERA),true)
PRODUCT_PACKAGES += \
	SEC_Camera
endif

ifneq ($(PRODUCT_TAG),HTPC-EXYNOS4X12)
PRODUCT_PACKAGES += Camera
endif

PRODUCT_PACKAGES += \
    Superuser \
    su
    
# Libs
PRODUCT_PACKAGES += \
	libstagefrighthw \
	com.android.future.usb.accessory

# Video Editor
PRODUCT_PACKAGES += \
	VideoEditorGoogle

# Misc other modules
PRODUCT_PACKAGES += \
	lights.$(TARGET_PRODUCT) \
	hwcomposer.exynos4

PRODUCT_PACKAGES += sensors.$(TARGET_PRODUCT)

# OpenMAX IL configuration files
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/media_profiles.xml:system/etc/media_profiles.xml

# OpenMAX IL modules
PRODUCT_PACKAGES += \
	libSEC_OMX_Core \
	libSEC_OMX_Resourcemanager \
	libOMX.SEC.AVC.Decoder \
	libOMX.SEC.M4V.Decoder \
	libOMX.SEC.M4V.Encoder \
	libOMX.SEC.AVC.Encoder

# hwconvertor modules
PRODUCT_PACKAGES += \
	libhwconverter \
	libswconverter \
	libswscaler

# MFC firmware
PRODUCT_COPY_FILES += \
	hardware/samsung_slsi/exynos4/firmware/mfc_fw.bin:system/vendor/firmware/mfc_fw.bin

PRODUCT_COPY_FILES += \
	frameworks/native/data/etc/android.hardware.touchscreen.multitouch.jazzhand.xml:system/etc/permissions/android.hardware.touchscreen.multitouch.jazzhand.xml \
	frameworks/native/data/etc/android.hardware.location.gps.xml:system/etc/permissions/android.hardware.location.gps.xml \
	frameworks/native/data/etc/android.hardware.usb.host.xml:system/etc/permissions/android.hardware.usb.host.xml \
	frameworks/native/data/etc/android.hardware.usb.accessory.xml:system/etc/permissions/android.hardware.usb.accessory.xml \
	frameworks/native/data/etc/android.hardware.audio.low_latency.xml:system/etc/permissions/android.hardware.audio.low_latency.xml \
	frameworks/native/data/etc/android.hardware.wifi.xml:system/etc/permissions/android.hardware.wifi.xml \
	packages/wallpapers/LivePicker/android.software.live_wallpaper.xml:system/etc/permissions/android.software.live_wallpaper.xml

# Widevine DRM
PRODUCT_PACKAGES += com.google.widevine.software.drm.xml \
	com.google.widevine.software.drm \
	WidevineSamplePlayer \
	test-libwvm \
	test-wvdrmplugin \
	test-wvplayer_L1 \
	libdrmwvmplugin \
	libwvm \
	libWVStreamControlAPI_L1 \
	libwvdrm_L1

# FIMC-IS firmware
PRODUCT_COPY_FILES += \
	hardware/samsung_slsi/exynos4/firmware/fimc_is_fw.bin:system/vendor/firmware/fimc_is_fw.bin \
	hardware/samsung_slsi/exynos4/firmware/setfile.bin:system/vendor/firmware/setfile.bin \
	hardware/samsung_slsi/exynos4/firmware/setfile_S5K3H7.bin:system/vendor/firmware/setfile_S5K3H7.bin

# Input device calibration files
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/s5pc210_ts.idc:system/usr/idc/s5pc210_ts.idc \
	$(LOCAL_PATH)/pixcir-i2c-ts.idc:system/usr/idc/pixcir-i2c-ts.idc \
	$(LOCAL_PATH)/mixtile_ts.idc:system/usr/idc/mixtile_ts.idc \
	$(LOCAL_PATH)/pixcir_usb_ts.idc:system/usr/idc/pixcir_usb_ts.idc

# The OpenGL ES API level that is natively supported by this device.
# This is a 16.16 fixed point number
PRODUCT_PROPERTY_OVERRIDES := \
	ro.opengles.version=131072

PRODUCT_PROPERTY_OVERRIDES += \
	debug.hwui.render_dirty_regions=false

# Set default USB interface
PRODUCT_DEFAULT_PROPERTY_OVERRIDES += \
	persist.sys.usb.config=mass_storage \
	ro.kernel.android.checkjni=0

# Device uses high-density artwork where available
PRODUCT_AAPT_CONFIG := normal hdpi xhdpi xxhdpi
PRODUCT_AAPT_PREF_CONFIG := xhdpi xxhdpi

PRODUCT_CHARACTERISTICS := tablet

# call dalvik heap config
$(call inherit-product-if-exists, frameworks/native/build/phone-xxhdpi-2048-dalvik-heap.mk)

# call hwui memory config
$(call inherit-product-if-exists, frameworks/native/build/phone-xxhdpi-2048-hwui-memory.mk)

PRODUCT_TAGS += dalvik.gc.type-precise

# Set default USB interface
# PRODUCT_DEFAULT_PROPERTY_OVERRIDES += persist.sys.usb.config=mass_storage
PRODUCT_DEFAULT_PROPERTY_OVERRIDES += persist.sys.usb.config=mtp

PRODUCT_CHARACTERISTICS := tablet

PRODUCT_COPY_FILES += \
	frameworks/native/data/etc/tablet_core_hardware.xml:system/etc/permissions/tablet_core_hardware.xml

PRODUCT_PACKAGES += \
	sqlite3 \
	stagefright

# we have enough storage space to hold precise GC data
PRODUCT_TAGS += dalvik.gc.type-precise

# hwconvertor modules
PRODUCT_PACKAGES += \
	libhwconverter
	
PRODUCT_PROPERTY_OVERRIDES += \
	ro.kernel.android.checkjni=0 \
	dalvik.vm.checkjni=false \
	windowsmgr.max_events_per_sec=240

PRODUCT_PROPERTY_OVERRIDES += \
	ro.sf.lcd_density=160
	
#for tools and preinstall apk
$(call inherit-product, $(LOCAL_PATH)/tools/copy_file.mk)

PRODUCT_DEFAULT_PROPERTY_OVERRIDES += persist.sys.language=el
PRODUCT_DEFAULT_PROPERTY_OVERRIDES += persist.sys.country=GR
PRODUCT_DEFAULT_PROPERTY_OVERRIDES += persist.sys.timezone=Europe/Athens

#for clear red frame
PRODUCT_PROPERTY_OVERRIDES += persist.sys.strictmode.visual=0
PRODUCT_PROPERTY_OVERRIDES += persist.sys.strictmode.disable=1

#for wifi
$(call inherit-product, $(LOCAL_PATH)/wifi/copy_file.mk)
PRODUCT_DEFAULT_PROPERTY_OVERRIDES += wifi.interface=wlan0
PRODUCT_DEFAULT_PROPERTY_OVERRIDES += wifi.supplicant_scan_interval=10

ifeq ($(WIFI_RTL8188),true)
PRODUCT_COPY_FILES += \
	frameworks/native/data/etc/android.hardware.wifi.direct.xml:system/etc/permissions/android.hardware.wifi.direct.xml
endif

PRODUCT_PACKAGES += \
	libwapi 
	
#for led_torch
ifeq ($(USE_LED_TORCH),true)
PRODUCT_PACKAGES += Torch
endif

#for gapps
$(call inherit-product, $(LOCAL_PATH)/tools/gapps/copy_file.mk)
#PRODUCT_PROPERTY_OVERRIDES += gsm.sim.operator.numeric=31026
#PRODUCT_PROPERTY_OVERRIDES += gsm.sim.operator.alpha=T-Mobile
#PRODUCT_PROPERTY_OVERRIDES += gsm.sim.operator.iso-country=us

PRODUCT_COPY_FILES += $(LOCAL_PATH)/conf/apns-conf.xml:system/etc/apns-conf.xml
PRODUCT_PROPERTY_OVERRIDES += keyguard.no_require_sim=true
PRODUCT_PROPERTY_OVERRIDES += ro.com.android.dataroaming=true

#for DS-5 gapor
PRODUCT_PACKAGES += gatord

#for facelock
$(call inherit-product, $(LOCAL_PATH)/tools/gapps/facelock/copy_file.mk)

#for EETI USB Touch
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/eeti/eGalaxTouch_VirtualDevice.idc:system/usr/idc/eGalaxTouch_VirtualDevice.idc \
	$(LOCAL_PATH)/eeti/eGTouchD:system/bin/eGTouchD \
	$(LOCAL_PATH)/eeti/eGTouchA.ini:system/etc/eGTouchA.ini

