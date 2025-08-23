#pragma once

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <dlfcn.h>
#include <vector>

#include "imgui.h"
#include "imgui_impl_android.h"
#include "imgui_impl_opengl3.h"
#include "main.h"
#include "Struct/tools.hpp"

#include "Icon/OPPOSans-H.h"
#include "Icon/Icon.h"
#include "Icon/Iconcpp.h"
#include "Icon/Font.h"

#include <Struct/ESP.h>



inline static bool g_IsSetup = false;
inline int prevWidth, prevHeight;


inline void (*origInput)(void*, void*, void*);
inline void myInput(void *thiz, void *ex_ab, void *ex_ac) {
    origInput(thiz, ex_ab, ex_ac);
    ImGui_ImplAndroid_HandleInputEvent((AInputEvent *)thiz);
    return;
}


float density = -1;

ImFont *font;
/*
inline void SetupImgui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

   
    io.DisplaySize = ImVec2((float)g_GlWidth, (float)g_GlHeight);
   
     
    ImGui::StyleColorsDark();
    
    
    ImGui_ImplOpenGL3_Init("#version 300 es");
    
    
    static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
            ImFontConfig icons_config;
   
           ImFontConfig CustomFont;
            CustomFont.FontDataOwnedByAtlas = false;

            icons_config.MergeMode = true;
            icons_config.PixelSnapH = true;
            icons_config.OversampleH = 2.5;
            icons_config.OversampleV = 2.5;
            
            
            io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Custom), sizeof(Custom), 20.f, &CustomFont);
            io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 20.0f, &icons_config, icons_ranges);

            ImFontConfig cfg;
            cfg.SizePixels = ((float) density / 20.0f);
            io.Fonts->AddFontDefault(&cfg);

    // Arbitrary scale-up
    ImGui::GetStyle().ScaleAllSizes(3.0f);
}
*/



void SetupImgui() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle* style = &ImGui::GetStyle();
    io.DisplaySize = ImVec2((float)g_GlWidth, (float)g_GlHeight);

    ImGui::StyleColorsDark();
    
    style->WindowRounding = 5.3f;
    style->FrameRounding = 2.3f;
    style->ScrollbarRounding = 0;
    style->WindowTitleAlign = ImVec2(0.5, 0.5);        
    style->FramePadding = ImVec2(8, 6);
    style->ScaleAllSizes(1.0f);
    style->ScrollbarSize /= 1;

    
    ImGui_ImplOpenGL3_Init("#version 300 es");
    
    // We load the default font with increased size to improve readability on many devices with "high" DPI.
    ImFontConfig font_cfg;
    font_cfg.SizePixels = 22.0f;
    io.Fonts->AddFontDefault(&font_cfg);

    // Arbitrary scale-up
    ImGui::GetStyle().ScaleAllSizes(3.0f);
}

// ===== ADVANCED THEME FUNCTIONS FROM NEW JNI =====
#define colors style->Colors

namespace AdvancedThemes {
    void SetAllanTheme() {
        ImGuiStyle *style = &ImGui::GetStyle();
        colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.47f, 0.77f, 0.83f, 1.00f);
        colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 1.00f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.32f, 0.27f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.11f, 0.74f, 0.00f, 1.00f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.07f, 0.70f, 0.01f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.43f, 0.24f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.67f, 0.01f, 1.00f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.43f, 0.24f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.19f, 0.76f, 0.00f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.03f, 0.70f, 0.06f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.71f, 0.39f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.02f, 0.59f, 0.38f, 1.00f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 0.49f, 0.51f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.00f, 0.43f, 0.24f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.08f, 0.77f, 0.03f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.08f, 0.72f, 0.00f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.11f, 0.64f, 0.00f, 1.00f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.03f, 0.70f, 0.01f, 1.00f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.05f, 0.72f, 0.01f, 1.00f);
        colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.391f, 0.391f, 0.391f, 1.00f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 1.00f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.00f, 0.55f, 0.12f, 1.00f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.00f, 0.71f, 0.01f, 1.00f);
        colors[ImGuiCol_Tab] = ImVec4(0.098f, 0.098f, 0.098f, 1.00f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.352f, 0.352f, 0.352f, 1.00f);
        colors[ImGuiCol_TabActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.00f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.098f, 0.098f, 0.098f, 1.00f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.00f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.05f, 0.64f, 0.01f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.04f, 0.70f, 0.02f, 1.00f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.02f, 0.57f, 0.00f, 1.00f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(1.000f, 0.391f, 0.000f, 1.00f);
        colors[ImGuiCol_NavHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.00f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
        
        style->ItemSpacing = ImVec2(10, 2);
        style->IndentSpacing = 12;
        style->ScrollbarSize = 10;
        style->WindowRounding = 4;
        style->FrameRounding = 4;
        style->PopupRounding = 4;
        style->ScrollbarRounding = 6;
        style->GrabRounding = 4;
        style->TabRounding = 4;
        style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
        style->DisplaySafeAreaPadding = ImVec2(4, 4);
    }

    void SetDarkTheme() {
        ImGuiStyle *style = &ImGui::GetStyle();
        style->FrameRounding = 10.0f;
        style->GrabRounding = 4.0f;
        style->WindowRounding = 10.0f;
        style->FrameBorderSize = 4.0f;
        style->WindowBorderSize = 3.00;
        style->WindowTitleAlign = ImVec2(0.5, 0.5);

        style->Colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
        style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
        style->Colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
        style->Colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
        style->Colors[ImGuiCol_PopupBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
        style->Colors[ImGuiCol_Border] = ImColor(0, 255, 47);
        style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style->Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00);
        style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
        style->Colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
        style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
        style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
        style->Colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
        style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
        style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
        style->Colors[ImGuiCol_Button] = ImColor(0, 255, 47);
        style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.94f, 0.39f, 0.13f, 1.00f);
        style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
        style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.15f, 0.19f, 0.55f);
        style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.16f, 0.19f, 0.15f, 1.00f);
        style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.16f, 0.19f, 0.15f, 1.00f);
        style->Colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
        style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
        style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
        style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
        style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
        style->Colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        style->Colors[ImGuiCol_TabHovered] = ImVec4(0.48f, 0.77f, 0.46f, 0.80f);
        style->Colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        style->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
        style->Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        style->Colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        style->Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        style->Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        style->Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
        style->ScrollbarSize /= 1;
    }
}
// ===== END ADVANCED THEME FUNCTIONS =====


JavaVM *jvm;
JNIEnv *genv;



std::string getClipboard() {
    std::string result;
    
    jvm->AttachCurrentThread(&genv, NULL);
    
    auto looperClass = genv->FindClass(OBFUSCATE("android/os/Looper"));
    auto prepareMethod = genv->GetStaticMethodID(looperClass, OBFUSCATE("prepare"), OBFUSCATE("()V"));
    genv->CallStaticVoidMethod(looperClass, prepareMethod);
    
    jclass activityThreadClass = genv->FindClass(OBFUSCATE("android/app/ActivityThread"));
    jfieldID sCurrentActivityThreadField = genv->GetStaticFieldID(activityThreadClass, OBFUSCATE("sCurrentActivityThread"), OBFUSCATE("Landroid/app/ActivityThread;"));
    jobject sCurrentActivityThread = genv->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);
    
    jfieldID mInitialApplicationField = genv->GetFieldID(activityThreadClass, OBFUSCATE("mInitialApplication"), OBFUSCATE("Landroid/app/Application;"));
    jobject mInitialApplication = genv->GetObjectField(sCurrentActivityThread, mInitialApplicationField);
    
    auto contextClass = genv->FindClass(OBFUSCATE("android/content/Context"));
    auto getSystemServiceMethod = genv->GetMethodID(contextClass, OBFUSCATE("getSystemService"), OBFUSCATE("(Ljava/lang/String;)Ljava/lang/Object;"));
    
    auto str = genv->NewStringUTF(OBFUSCATE("clipboard"));
    auto clipboardManager = genv->CallObjectMethod(mInitialApplication, getSystemServiceMethod, str);
    genv->DeleteLocalRef(str);
    
    jclass ClipboardManagerClass = genv->FindClass(OBFUSCATE("android/content/ClipboardManager"));
    auto getText = genv->GetMethodID(ClipboardManagerClass, OBFUSCATE("getText"), OBFUSCATE("()Ljava/lang/CharSequence;"));

    jclass CharSequenceClass = genv->FindClass(OBFUSCATE("java/lang/CharSequence"));
    auto toStringMethod = genv->GetMethodID(CharSequenceClass, OBFUSCATE("toString"), OBFUSCATE("()Ljava/lang/String;"));

    auto text = genv->CallObjectMethod(clipboardManager, getText);
    if (text) {
        str = (jstring) genv->CallObjectMethod(text, toStringMethod);
        result = genv->GetStringUTFChars(str, 0);
        genv->DeleteLocalRef(str);
        genv->DeleteLocalRef(text);
    }
    genv->DeleteLocalRef(CharSequenceClass);
    genv->DeleteLocalRef(ClipboardManagerClass);
    genv->DeleteLocalRef(clipboardManager);
    genv->DeleteLocalRef(contextClass);
    genv->DeleteLocalRef(mInitialApplication);
    genv->DeleteLocalRef(activityThreadClass);   
    jvm->DetachCurrentThread();
    return result.c_str();
}

jclass UnityPlayer_cls;
jfieldID UnityPlayer_CurrentActivity_fid;



jobject getGlobalContext()
{
    jclass activityThread = genv->FindClass(OBFUSCATE("android/app/ActivityThread"));
    jmethodID currentActivityThread = genv->GetStaticMethodID(activityThread, OBFUSCATE("currentActivityThread"), OBFUSCATE("()Landroid/app/ActivityThread;"));
    jobject at = genv->CallStaticObjectMethod(activityThread, currentActivityThread);
    jmethodID getApplication = genv->GetMethodID(activityThread, OBFUSCATE("getApplication"), OBFUSCATE("()Landroid/app/Application;"));
    jobject context = genv->CallObjectMethod(at, getApplication);
    return context;
}

void displayKeyboard(bool pShow) {
    jclass ctx = genv->FindClass(OBFUSCATE("android/content/Context"));
    jfieldID fid = genv->GetStaticFieldID(ctx, OBFUSCATE("INPUT_METHOD_SERVICE"), OBFUSCATE("Ljava/lang/String;"));
    jmethodID mid = genv->GetMethodID(ctx, OBFUSCATE("getSystemService"), OBFUSCATE("(Ljava/lang/String;)Ljava/lang/Object;"));
    jobject context = genv->GetStaticObjectField(UnityPlayer_cls, UnityPlayer_CurrentActivity_fid);
    jobject InputManObj = genv->CallObjectMethod(context, mid, (jstring) genv->GetStaticObjectField(ctx, fid));
    jclass ClassInputMethodManager = genv->FindClass(OBFUSCATE("android/view/inputmethod/InputMethodManager"));
    jmethodID toggleSoftInputId = genv->GetMethodID(ClassInputMethodManager, OBFUSCATE("toggleSoftInput"), OBFUSCATE("(II)V"));
    if (pShow) {
        genv->CallVoidMethod(InputManObj, toggleSoftInputId, 2, 0);
    } else {
        genv->CallVoidMethod(InputManObj, toggleSoftInputId, 0, 0);
    }
}

int ShowSoftKeyboardInput() {
    jint result;
    jint flags = 0;
    
    JNIEnv *env;
    jvm->AttachCurrentThread(&env, NULL);
    
    jclass looperClass = env->FindClass(OBFUSCATE("android/os/Looper"));
    auto prepareMethod = env->GetStaticMethodID(looperClass, OBFUSCATE("prepare"), OBFUSCATE("()V"));
    env->CallStaticVoidMethod(looperClass, prepareMethod);
    
    jclass activityThreadClass = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
    jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, OBFUSCATE("sCurrentActivityThread"), OBFUSCATE("Landroid/app/ActivityThread;"));
    jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);
    
    jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, OBFUSCATE("mInitialApplication"), OBFUSCATE("Landroid/app/Application;"));
    jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);
    
    jclass contextClass = env->FindClass(OBFUSCATE("android/content/Context"));
    jfieldID fieldINPUT_METHOD_SERVICE = env->GetStaticFieldID(contextClass, OBFUSCATE("INPUT_METHOD_SERVICE"), OBFUSCATE("Ljava/lang/String;"));
    jobject INPUT_METHOD_SERVICE = env->GetStaticObjectField(contextClass, fieldINPUT_METHOD_SERVICE);
    jmethodID getSystemServiceMethod = env->GetMethodID(contextClass, OBFUSCATE("getSystemService"), OBFUSCATE("(Ljava/lang/String;)Ljava/lang/Object;"));
    jobject callObjectMethod = env->CallObjectMethod(mInitialApplication, getSystemServiceMethod, INPUT_METHOD_SERVICE);
    
    jclass classInputMethodManager = env->FindClass(OBFUSCATE("android/view/inputmethod/InputMethodManager"));
    jmethodID toggleSoftInputId = env->GetMethodID(classInputMethodManager, OBFUSCATE("toggleSoftInput"), OBFUSCATE("(II)V"));
    
    if (result) {
        env->CallVoidMethod(callObjectMethod, toggleSoftInputId, 2, flags);
    } else {
        env->CallVoidMethod(callObjectMethod, toggleSoftInputId, flags, flags);
    }
    
    env->DeleteLocalRef(classInputMethodManager);
    env->DeleteLocalRef(callObjectMethod);
    env->DeleteLocalRef(contextClass);
    env->DeleteLocalRef(mInitialApplication);
    env->DeleteLocalRef(activityThreadClass);
    jvm->DetachCurrentThread();
    
    return result;
}



struct UnityEngine_Vector2_Fields {
    float x;
    float y;
};

struct UnityEngine_Vector2_o {
    UnityEngine_Vector2_Fields fields;
};

enum TouchPhase {
    Began = 0,
    Moved = 1,
    Stationary = 2,
    Ended = 3,
    Canceled = 4
};

struct UnityEngine_Touch_Fields {
    int32_t m_FingerId;
    struct UnityEngine_Vector2_o m_Position;
    struct UnityEngine_Vector2_o m_RawPosition;
    struct UnityEngine_Vector2_o m_PositionDelta;
    float m_TimeDelta;
    int32_t m_TapCount;
    int32_t m_Phase;
    int32_t m_Type;
    float m_Pressure;
    float m_maximumPossiblePressure;
    float m_Radius;
    float m_RadiusVariance;
    float m_AltitudeAngle;
    float m_AzimuthAngle;
};


