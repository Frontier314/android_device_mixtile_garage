LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= bat_test.c
LOCAL_MODULE := bat_test
LOCAL_SHARED_LIBRARIES:= libcutils libutils
LOCAL_MODULE_TAGS := eng

include $(BUILD_EXECUTABLE)
