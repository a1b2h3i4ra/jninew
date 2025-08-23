LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libdobby
#LOCAL_SRC_FILES := $(LOCAL_PATH)/DobbyHook/$(TARGET_ARCH_ABI)/libdobby.a
LOCAL_SRC_FILES := DobbyHook/$(TARGET_ARCH_ABI)/libdobby.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := $(TARGET_ARCH_ABI)

# -std=c++17 is required to support AIDE app with NDK
LOCAL_CFLAGS := -w -s -Wno-error=format-security -fvisibility=hidden -fpermissive -fexceptions
LOCAL_CPPFLAGS := -w -s -Wno-error=format-security -fvisibility=hidden -Werror -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fpermissive -Wall -fexceptions
LOCAL_LDFLAGS += -Wl,--gc-sections,--strip-all,-llog
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2
LOCAL_ARM_MODE := arm

LOCAL_STATIC_LIBRARIES := libdobby

LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/KenzGUI/ImGui
LOCAL_C_INCLUDES += $(LOCAL_PATH)/KenzGUI/ImGui/backends

# Here you add the cpp file to compile
LOCAL_SRC_FILES := Kenz.cpp \
    ByNameModding/Tools.cpp \
    ByNameModding/fake_dlfcn.cpp \
    ByNameModding/Il2Cpp.cpp \
	KenzGUI/Substrate/hde64.c \
	KenzGUI/Substrate/SubstrateDebug.cpp \
	KenzGUI/Substrate/SubstrateHook.cpp \
	KenzGUI/Substrate/SubstratePosixMemory.cpp \
	KenzGUI/Substrate/SymbolFinder.cpp \
	KenzGUI/KittyMemory/KittyMemory.cpp \
	KenzGUI/KittyMemory/MemoryPatch.cpp \
    KenzGUI/KittyMemory/MemoryBackup.cpp \
    KenzGUI/KittyMemory/KittyUtils.cpp \
	KenzGUI/And64InlineHook/And64InlineHook.cpp \
	KenzGUI/ImGui/imgui.cpp \
	KenzGUI/ImGui/imgui_draw.cpp \
	KenzGUI/ImGui/imgui_demo.cpp \
	KenzGUI/ImGui/imgui_widgets.cpp \
	KenzGUI/ImGui/imgui_tables.cpp \
	KenzGUI/ImGui/backends/imgui_impl_opengl3.cpp \

include $(BUILD_SHARED_LIBRARY)
