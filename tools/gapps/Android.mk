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

#for gapps
$(call add-prebuilt-file-apk, ETC, app/ChromeBookmarksSyncAdapter.apk, app/ChromeBookmarksSyncAdapter)
$(call add-prebuilt-file-apk, ETC, app/GoogleBackupTransport.apk, app/GoogleBackupTransport)
$(call add-prebuilt-file-apk, ETC, app/GoogleCalendarSyncAdapter.apk, app/GoogleCalendarSyncAdapter)
$(call add-prebuilt-file-apk, ETC, app/GoogleContactsSyncAdapter.apk, app/GoogleContactsSyncAdapter)
$(call add-prebuilt-file-apk, ETC, app/GoogleFeedback.apk, app/GoogleFeedback)
$(call add-prebuilt-file-apk, ETC, app/GoogleLoginService.apk, app/GoogleLoginService)
$(call add-prebuilt-file-apk, ETC, app/GooglePartnerSetup.apk, app/GooglePartnerSetup)
$(call add-prebuilt-file-apk, ETC, app/GoogleServicesFramework.apk, app/GoogleServicesFramework)
$(call add-prebuilt-file-apk, ETC, app/GoogleTTS.apk, app/GoogleTTS)
$(call add-prebuilt-file-apk, ETC, app/MarketUpdater.apk, app/MarketUpdater)
$(call add-prebuilt-file-apk, ETC, app/MediaUploader.apk, app/MediaUploader)
$(call add-prebuilt-file-apk, ETC, app/NetworkLocation.apk, app/NetworkLocation)
$(call add-prebuilt-file-apk, ETC, app/VoiceSearch.apk, app/VoiceSearch)
$(call add-prebuilt-file-apk, ETC, app/GenieWidget.apk, app/GenieWidget)
$(call add-prebuilt-file-apk, ETC, app/Phonesky.apk, app/Phonesky)

#for face lock
$(call add-prebuilt-file-apk, ETC, facelock/app/FaceLock.apk, app/FaceLock)
$(call add-prebuilt-file-lib, ETC, facelock/lib/libfacelock_jni.so, libfacelock_jni)
