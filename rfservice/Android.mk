LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= BtCtl.cpp
LOCAL_SHARED_LIBRARIES := libutils libbinder
LOCAL_MODULE_TAGS:=optional
LOCAL_MODULE := libBtCtl
LOCAL_PRELINK_MODULE:= false
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= BtCtlService.cpp
LOCAL_SHARED_LIBRARIES:= libutils liblog libbinder
LOCAL_MODULE_TAGS:= optional
LOCAL_MODULE:= libBtCtlService
LOCAL_PRELINK_MODULE:= false
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= bt_ctl_server.cpp
LOCAL_SHARED_LIBRARIES:= libutils libbinder liblog 
LOCAL_STATIC_LIBRARIES:= libBtCtlService
LOCAL_MODULE_TAGS:= optional
LOCAL_MODULE:= bt_ctl_server
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= bt_pwr.cpp
LOCAL_SHARED_LIBRARIES:= libutils libbinder liblog 
LOCAL_STATIC_LIBRARIES:= libBtCtl
LOCAL_MODULE_TAGS:= optional
LOCAL_MODULE := .bt_pwr
include $(BUILD_EXECUTABLE)

