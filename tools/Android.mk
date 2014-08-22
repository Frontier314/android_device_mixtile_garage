# Copyright (C) 2008 The Android Open Source Project
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

# http://blog.csdn.net/dzhj11/article/details/7319580
# ETC,APPS,EXECUTABLES,SHARED_LIBRARIES,STATIC_LIBRARIES 
#/////////////////////////////////////////////////////////////////////////////////////////
define add-prebuilt-file-apk
    $(eval $(include-prebuilt-apk))
endef

define include-prebuilt-apk
    include $$(CLEAR_VARS)
    LOCAL_MODULE := $(3)
    LOCAL_SRC_FILES := $(2)
    LOCAL_MODULE_PATH := $(TARGET_OUT)
    LOCAL_MODULE_TAGS := eng
    LOCAL_MODULE_CLASS := $(1)
    LOCAL_MODULE_SUFFIX := $$(suffix $(2))
    LOCAL_CERTIFICATE := platform
    include $(BUILD_PREBUILT)
endef

#/////////////////////////////////////////////////////////////////////////////////////////

#/////////////////////////////////////////////////////////////////////////////////////////
define add-prebuilt-file-lib
    $(eval $(include-prebuilt-lib))
endef

define include-prebuilt-lib
    include $$(CLEAR_VARS)
    LOCAL_MODULE := $(3)
    LOCAL_SRC_FILES := $(2)
    LOCAL_MODULE_PATH := $(TARGET_OUT)/lib
    LOCAL_MODULE_TAGS := eng
    LOCAL_MODULE_CLASS := $(1)
    LOCAL_MODULE_SUFFIX := $$(suffix $(2))
    include $(BUILD_PREBUILT)
endef

#/////////////////////////////////////////////////////////////////////////////////////////

LOCAL_PATH := $(call my-dir)

#for preinstall apps
$(call add-prebuilt-file-apk, ETC, preinstall/DicePlayer.apk, preinstall/DicePlayer)

$(call add-prebuilt-file-apk, ETC, preinstall/AdebeFlashPlayer.apk, preinstall/AdebeFlashPlayer)
$(call add-prebuilt-file-apk, ETC, preinstall/Maps.apk, preinstall/Maps)
$(call add-prebuilt-file-apk, ETC, preinstall/Street.apk, preinstall/Street)
$(call add-prebuilt-file-apk, ETC, preinstall/Gmail.apk, preinstall/Gmail)
$(call add-prebuilt-file-apk, ETC, preinstall/OIFileManager.apk, preinstall/OIFileManager)
$(call add-prebuilt-file-apk, ETC, preinstall/MxPlayer.apk, preinstall/MxPlayer)
$(call add-prebuilt-file-apk, ETC, preinstall/MxPlayerCodec_neon.apk, preinstall/MxPlayerCodec_neon)

$(call add-prebuilt-file-apk, ETC, other/AdobeReader/AdobeReader.apk, app/AdobeReader)
$(call add-prebuilt-file-lib, ETC, other/AdobeReader/libAdobeReader.so, libAdobeReader)
$(call add-prebuilt-file-apk, ETC, other/SuperUser.apk, app/SuperUser)
$(call add-prebuilt-file-apk, ETC, other/iFlyIME/iFlyIME_Pad.apk, app/iFlyIME_Pad)
$(call add-prebuilt-file-lib, ETC, other/iFlyIME/libmsc-v3.so, libmsc-v3)
$(call add-prebuilt-file-lib, ETC, other/iFlyIME/libsmartaiwrite-jni-v4.so, libsmartaiwrite-jni-v4)
$(call add-prebuilt-file-lib, ETC, other/iFlyIME/libvadLib-v2.so, libvadLib-v2)

ifeq ($(PRODUCT_MODEL),HTPC-EXYNOS4X12)
$(call add-prebuilt-file-apk, ETC, preinstall/CameraZOOMFX.apk, preinstall/CameraZOOMFX)
endif

include $(call all-makefiles-under,$(LOCAL_PATH))
