LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := maxwell_encrypt
LOCAL_SRC_FILES := EncryptUtils.cpp DecryptAPI.cpp Tools.cpp
LOCAL_CFLAGS    := -fvisibility=hidden -fno-stack-protector -Wall -Wno-address-of-array-temporary
LOCAL_LDLIBS    += -llog
include $(BUILD_SHARED_LIBRARY)