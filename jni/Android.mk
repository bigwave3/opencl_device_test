LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := CLDeviceTest
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include
LOCAL_LDLIBS := $(LOCAL_PATH)/../external/libGLES_mali.so
LOCAL_SRC_FILES := device_test.c
LOCAL_ARM_MODE  := arm

include $(BUILD_SHARED_LIBRARY)
