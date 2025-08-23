#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include <android/log.h>
#include <xdl.h>
#include <KittyUtils.h>
#include <KittyMemory.h>
#include <Il2Cpp.h>
#include <SubstrateHook.h>
#include <CydiaSubstrate.h>
#include "KenzGUI/CallGUI_.h"
#include "DrawMenu.h"
#define targetLib "libil2cpp.so"
#include "Hooks.h"
#include "ESP.h"
#include "Zygisk/zygisk.h"

using zygisk::Api;
using zygisk::AppSpecializeArgs;
using zygisk::ServerSpecializeArgs;
 



// ===================================================== //
// Free Fire Max Package Target
#define targetPackageName OBFUSCATE("com.dts.freefiremax")

uintptr_t G_IL2CPP;
uintptr_t il2cpp_base = 0;

// Free Fire specific offsets from CS file
#define HEALTH_OFFSET 0x7b45840
#define AMMO_OFFSET 0x7c25b54
#define CURRENCY_OFFSET 0x25ffe14
#define PLAYER_CONTROLLER_OFFSET 0x8800054

// ESP and Aimbot variables from old JNI
bool Enable = false;
bool Aimbot = false;
float Fov_Aim = 100.0f;
float Aimdis = 500.0f;
int AimWhen = 1;
const char* dir[] = {"None","Fire","Scope"};

// ESP Configuration
struct cfg {
    bool aimbot;
    int aim_type = 0;
    int aim_target = 1;
    struct _esp {
        bool Box;
        bool Line;
        bool Health;
        bool Distance;
        bool IsName;
        bool Path;       
        bool Esp360;
        bool Target;
    }ESP;
}Config;

// Colors for ESP
ImColor Esp_Box = ImColor(255,255,255,229);
ImColor Esp_Text = ImColor(255,255,255,229);
ImColor hp = ImColor(0,255,0,255);
ImColor die = ImColor(255,0,0);

// Free Fire specific functions
void *getRealAddr(ulong offset) {
    return reinterpret_cast<void*>(il2cpp_base + offset);
}


#include <ctime>
#include <cstdio>

void DrawNetBackground(const ImVec2& window_pos, const ImVec2& window_size, float time) {
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    // Parameters for the net
    const float grid_spacing = 40.0f; // Distance between grid points
    const float amplitude = 5.0f;     // Amount of vertical oscillation for animation
    const int cols = static_cast<int>(window_size.x / grid_spacing) + 2;
    const int rows = static_cast<int>(window_size.y / grid_spacing) + 2;

    ImU32 line_color = ImGui::GetColorU32(ImVec4(0.0f, 0.6f, 0.0f, 0.6f)); // Semi-transparent green
    ImU32 point_color = ImGui::GetColorU32(ImVec4(0.0f, 1.0f, 0.0f, 0.8f)); // Bright green for points

    // Store points with animation offset
    std::vector<ImVec2> points(rows * cols);

    // Calculate points with vertical wave animation
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = window_pos.x + col * grid_spacing;
            float y = window_pos.y + row * grid_spacing;

            // Animate y with sine wave based on time and position for glowing wave effect
            float offset = sinf(time * 3.0f + (col + row) * 0.5f) * amplitude;
            points[row * cols + col] = ImVec2(x, y + offset);
        }
    }

    // Draw horizontal lines
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols - 1; ++col) {
            draw_list->AddLine(points[row * cols + col], points[row * cols + col + 1], line_color, 1.0f);
        }
    }

    // Draw vertical lines
    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row < rows - 1; ++row) {
            draw_list->AddLine(points[row * cols + col], points[(row + 1) * cols + col], line_color, 1.0f);
        }
    }

    // Draw points
    for (const auto& pt : points) {
        draw_list->AddCircleFilled(pt, 2.0f, point_color);
    }
}


ImVec4 RainbowColor(float t) {
    float r = sinf(t * 6.283185f) * 0.5f + 0.5f;
    float g = sinf(t * 6.283185f + 2.094f) * 0.5f + 0.5f;
    float b = sinf(t * 6.283185f + 4.188f) * 0.5f + 0.5f;
    return ImVec4(r, g, b, 1.0f);
}

time_t GetExpiryTimestamp(const char* expiry_date_str) {
    // expiry_date_str format is "DD-MM-YY"
    struct tm expiry_tm = {0};
    int day, month, year;
    if (sscanf(expiry_date_str, "%d-%d-%d", &day, &month, &year) != 3) {
        return 0; // invalid format fallback, never expires
    }
    expiry_tm.tm_mday = day;
    expiry_tm.tm_mon = month - 1; // tm_mon is 0-11
    expiry_tm.tm_year = (year < 100) ? (year + 100) : year; // 2000-based year (e.g., 25 -> 2025)
    expiry_tm.tm_hour = 0;
    expiry_tm.tm_min = 0;
    expiry_tm.tm_sec = 0;
    expiry_tm.tm_isdst = -1; // let system determine
    return mktime(&expiry_tm);
}


// Updated ESP Drawing Functions using old JNI implementation
void DrawESP(int screenWidth, int screenHeight) {
    DrawESPNew(screenWidth, screenHeight);
}

void DrawMenu() {
    // Set your expiry date here in DD-MM-YY format
    static time_t expiry_timestamp = GetExpiryTimestamp("28-08-25"); // Set your ModMenu Expiry date...so it will automatically expire your ModMenu according to date you set date/month/year
    
    time_t now = time(nullptr);
    ImVec2 window_size = ImGui::GetIO().DisplaySize;

    // If expired, show expiry message centered and skip rest of menu
    if (now > expiry_timestamp && expiry_timestamp != 0) {
        ImGui::SetNextWindowBgAlpha(0.75f);
        ImGui::SetNextWindowPos(ImVec2(window_size.x / 2, window_size.y / 2), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::Begin("EXPIRED", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "- Note : ModMenu is expired -");
        ImGui::End();
        return; // Prevent drawing the rest of the menu when expired
    }
		
    const ImVec2 windowDim = ImVec2(700, 700);
    ImGui::SetNextWindowSize(windowDim, ImGuiCond_Once);

    if (ImGui::Begin(ICON_FA_GAMEPAD " FREE FIRE MAX [x64/x32]")) {
		ImVec2 pos = ImGui::GetWindowPos();   
        ImVec2 size = ImGui::GetWindowSize(); 
		float Meow = ImGui::GetTime();
		DrawNetBackground(pos, size, Meow);
        static int activeTab = 0;
        float windowWidth = ImGui::GetContentRegionAvail().x;

        // Tab buttons layout
        float spacing = 8.0f;
        int tabCount = 3;
        float buttonWidth = (windowWidth - spacing * (tabCount - 1)) / tabCount;
        float buttonHeight = 48.0f;

        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        float time = ImGui::GetTime();

        auto TabButton = [&](const char* label, int id) {
            ImVec2 pos = ImGui::GetCursorScreenPos();
            ImGuiStyle& style = ImGui::GetStyle();

            float oldRounding = style.FrameRounding;
            style.FrameRounding = 0.0f;

            ImVec2 size(buttonWidth, buttonHeight);

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
            bool pressed = ImGui::Button(label, size);
            ImGui::PopStyleVar();

            if (pressed)
                activeTab = id;

            style.FrameRounding = oldRounding;

            if (activeTab == id) {
                ImVec2 min = pos;
                ImVec2 max = ImVec2(pos.x + size.x, pos.y + size.y);
                float thickness = 3.0f;
                int segments = 80;

                for (int i = 0; i < segments; i++) {
                    float t0 = (float)i / segments;
                    float t1 = (float)(i + 1) / segments;
                    float shift = time * 0.5f;
                    ImVec4 col0 = RainbowColor(t0 + shift);
                    ImU32 c0 = ImGui::GetColorU32(col0);

                    ImVec2 p0, p1;
                    if (i < segments / 4) {
                        p0 = ImVec2(min.x + size.x * (t0 * 4), min.y);
                        p1 = ImVec2(min.x + size.x * (t1 * 4), min.y);
                    } else if (i < segments / 2) {
                        float tt0 = (t0 - 0.25f) * 4;
                        float tt1 = (t1 - 0.25f) * 4;
                        p0 = ImVec2(max.x, min.y + size.y * tt0);
                        p1 = ImVec2(max.x, min.y + size.y * tt1);
                    } else if (i < 3 * segments / 4) {
                        float tt0 = (t0 - 0.5f) * 4;
                        float tt1 = (t1 - 0.5f) * 4;
                        p0 = ImVec2(max.x - size.x * tt0, max.y);
                        p1 = ImVec2(max.x - size.x * tt1, max.y);
                    } else {
                        float tt0 = (t0 - 0.75f) * 4;
                        float tt1 = (t1 - 0.75f) * 4;
                        p0 = ImVec2(min.x, max.y - size.y * tt0);
                        p1 = ImVec2(min.x, max.y - size.y * tt1);
                    }

                    draw_list->AddLine(p0, p1, c0, thickness);
                }
            }
        };

        // Draw tab buttons
        for (int i = 0; i < tabCount; i++) {
            if (i > 0) ImGui::SameLine(0, spacing);
            if (i == 0) TabButton(ICON_FA_EYE " ESP/Visuals", 0);
            else if (i == 1) TabButton(ICON_FA_CROSSHAIRS " Aimbot", 1);
            else if (i == 2) TabButton(ICON_FA_COGS " Modifications", 2);
        }

        ImGui::Separator();

        float spacingChild = 8.0f;

        // ESP/Visuals Tab
        if (activeTab == 0) {
            float halfWidth = (windowWidth - spacingChild) / 2.0f;

            ImGui::BeginChild("left", ImVec2(halfWidth, 0), true);
            ImGui::PushItemWidth(-1);
			
            ImGui::Text("ESP Features");
            ImGui::Separator();
            ImGui::Checkbox("Enable ESP", &Enable);          
            ImGui::Checkbox("ESP Box", &Config.ESP.Box); 
            ImGui::Checkbox("ESP Line", &Config.ESP.Line); 
            ImGui::Checkbox("ESP Health", &Config.ESP.Health);
            ImGui::Checkbox("ESP Distance", &Config.ESP.Distance);
            ImGui::Checkbox("ESP Name", &Config.ESP.IsName);
            ImGui::Checkbox("Target Enemy", &Config.ESP.Target);
			
            ImGui::PopItemWidth();
            ImGui::EndChild();

            ImGui::SameLine(0, spacingChild);

            ImGui::BeginChild("right", ImVec2(0, 0), true);
            ImGui::PushItemWidth(-1);
            
            ImGui::Text("Visual Modifications");
            ImGui::Separator();
            ImGui::Checkbox("No Recoil", &Dummytoggle8);
            ImGui::Checkbox("No Spread", &Dummytoggle9);
            ImGui::Checkbox("High FOV", &Dummytoggle10);
            ImGui::Checkbox("Speed Hack", &Dummytoggle11);
            
            ImGui::PopItemWidth();
            ImGui::EndChild();
        }

        // Aimbot Tab
        if (activeTab == 1) {
            ImGui::BeginChild("aimbot_tab", ImVec2(0, 0), true);
            ImGui::PushItemWidth(-1);
            
            ImGui::Text("Aimbot Configuration");
            ImGui::Separator();
            ImGui::Checkbox("Enable Aimbot", &Aimbot);                           
            ImGui::Combo("Aim Mode", &AimWhen, dir, IM_ARRAYSIZE(dir));
            ImGui::SliderFloat("FOV Range", &Fov_Aim, 0.0f, 500.0f, "%.f");  
            ImGui::SliderFloat("Max Distance", &Aimdis, 0.0f, 1000.0f, "%.f");
            
            ImGui::PopItemWidth();
            ImGui::EndChild();
        }

        // Modifications Tab
        if (activeTab == 2) {
            ImGui::BeginChild("mods_tab", ImVec2(0, 0), true);
            ImGui::PushItemWidth(-1);
            
            ImGui::Text("Game Modifications");
            ImGui::Separator();
            ImGui::Checkbox("Unlimited Diamonds", &IsIntExample2);
            ImGui::Checkbox("God Mode", &Dummytoggle12);
            ImGui::Checkbox("Unlimited Ammo", &Dummytoggle13);
            ImGui::Checkbox("Fast Run", &Dummytoggle14);
            ImGui::Checkbox("Jump Hack", &Dummytoggle15);
            
            ImGui::PopItemWidth();
            ImGui::EndChild();
        }

        ImGui::End();
    }
}





// Dark Gray Theme from old JNI
void SetDarkGrayTheme() {
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

    colors[ImGuiCol_Text]                   = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
    colors[ImGuiCol_Border]                 = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
    colors[ImGuiCol_CheckMark]              = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_Button]                 = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);

    style->ChildRounding = 4.0f;
    style->FrameBorderSize = 1.0f;
    style->FrameRounding = 2.0f;
    style->GrabMinSize = 7.0f;
    style->PopupRounding = 2.0f;
    style->ScrollbarRounding = 12.0f;
    style->ScrollbarSize = 13.0f;
    style->TabBorderSize = 1.0f;
    style->TabRounding = 0.0f;
    style->WindowRounding = 4.0f;
}

EGLBoolean (*old_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    static bool is_setup = false;
    static bool should_clear_mouse_pos = false;
    if (!is_setup) {
		SetGUI();
        is_setup = true;
    }
	
    ImGuiIO &io = ImGui::GetIO();
    SetDarkGrayTheme();
    int (*TouchCount)(void*) = (int (*)(void*)) (Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Input"), OBFUSCATE("get_touchCount"), 0));
    int touchCount = TouchCount(nullptr);
    if (touchCount > 0) {
        UnityEngine_Touch_Fields touch = ((UnityEngine_Touch_Fields (*)(int)) (Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Input"), OBFUSCATE("GetTouch"), 1))) (0);
        float reverseY = io.DisplaySize.y - touch.m_Position.fields.y;

        switch (touch.m_Phase) {
            case TouchPhase::Began:
            case TouchPhase::Stationary:
                io.MousePos = ImVec2(touch.m_Position.fields.x, reverseY);
                io.MouseDown[0] = true;
                break;
            case TouchPhase::Ended:
            case TouchPhase::Canceled:
                io.MouseDown[0] = false;
                should_clear_mouse_pos = true;
                break;
            case TouchPhase::Moved:
                io.MousePos = ImVec2(touch.m_Position.fields.x, reverseY);
                break;
            default:
                break;
        }
    } else {
        io.MouseDown[0] = false;
    }

    DrawESP(io.DisplaySize.x, io.DisplaySize.y);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    DrawMenu();
	ImGui::Render();
    glViewport(0, 0, static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y));
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::EndFrame();
    if (should_clear_mouse_pos) {
        io.MousePos = ImVec2(-1, -1);
        should_clear_mouse_pos = false;
    }
    return old_eglSwapBuffers(dpy, surface);
}

// Additional Free Fire hook functions
bool (*old_GetHealth)(void *instance);
bool GetHealth(void *instance) {
    if (instance != NULL && Dummytoggle12) { // God Mode
        return true; // Always return healthy state
    }
    return old_GetHealth(instance);
}

int (*old_GetAmmo)(void *instance);
int GetAmmo(void *instance) {
    if (instance != NULL && Dummytoggle13) { // Unlimited Ammo
        return 9999;
    }
    return old_GetAmmo(instance);
}

float (*old_GetSpeed)(void *instance);
float GetSpeed(void *instance) {
    if (instance != NULL && Dummytoggle14) { // Fast Run
        return 10.0f; // Increased speed
    }
    return old_GetSpeed(instance);
}

// Recoil hook
float (*old_GetRecoil)(void *instance);
float GetRecoil(void *instance) {
    if (instance != NULL && Dummytoggle8) { // No Recoil
        return 0.0f; // Remove recoil
    }
    return old_GetRecoil(instance);
}

// FOV hook
float (*old_GetFOV)(void *instance);
float GetFOV(void *instance) {
    if (instance != NULL && Dummytoggle10) { // High FOV
        return 120.0f; // Increased FOV
    }
    return old_GetFOV(instance);
}

// Weapon spread hook
float (*old_GetSpread)(void *instance);
float GetSpread(void *instance) {
    if (instance != NULL && Dummytoggle9) { // No Spread
        return 0.0f; // Remove spread
    }
    return old_GetSpread(instance);
}

void *hack_start(void *) {
    while (!G_IL2CPP) {
        G_IL2CPP = Tools::GetBaseAddress(targetLib);
        il2cpp_base = G_IL2CPP;
        sleep(1);
    }
    
    Tools::Hook((void *) dlsym(RTLD_NEXT, "eglSwapBuffers"), (void *) hook_eglSwapBuffers, (void **) &old_eglSwapBuffers);
    Il2CppAttach();
    sleep(5);
	
    // Free Fire Max specific hooks using hardcoded offsets from CS file
    
    // Currency/Diamonds hook - Unlimited Diamonds
    Tools::Hook((void*)(il2cpp_base + CURRENCY_OFFSET), (void *) &IntExample2, (void **) &old_IntExample2);
    
    // Health hook for God Mode
    Tools::Hook((void*)(il2cpp_base + HEALTH_GET_OFFSET), (void *) &GetHealth, (void **) &old_GetHealth);
    
    // Ammo hook for Unlimited Ammo  
    Tools::Hook((void*)(il2cpp_base + AMMO_LEFT_OFFSET), (void *) &GetAmmo, (void **) &old_GetAmmo);
    
    // Speed hook for Fast Run
    Tools::Hook((void*)(il2cpp_base + SPEED_OFFSET), (void *) &GetSpeed, (void **) &old_GetSpeed);
    
    // Recoil hook for No Recoil
    Tools::Hook((void*)(il2cpp_base + RECOIL_OFFSET), (void *) &GetRecoil, (void **) &old_GetRecoil);
    
    // FOV hook for High FOV
    Tools::Hook((void*)(il2cpp_base + FOV_OFFSET), (void *) &GetFOV, (void **) &old_GetFOV);
    
    // Weapon spread hook for No Spread
    Tools::Hook((void*)(il2cpp_base + 0x7c25d7c), (void *) &GetSpread, (void **) &old_GetSpread);
    
    // Additional Free Fire Max specific hooks using extracted offsets from CS file
    // All these offsets are specifically for com.dts.freefiremax
	
    pthread_exit(nullptr);
    return nullptr;
}


class FreeFireMaxMod : public zygisk::ModuleBase {
public:
    void onLoad(Api *api, JNIEnv *env) override {
        this->api = api;
        this->env = env;
    }

    void preAppSpecialize(AppSpecializeArgs *args) override {
        static constexpr const char *packages[] = {
            "com.dts.freefiremax"
        }; // Only Free Fire Max package
        
        const char *process = env->GetStringUTFChars(args->nice_name, nullptr);
        for (const auto *package: packages) {
            is_game = (strcmp(process, package) == 0);
            if (is_game) {
                break;
            }
        }
        env->ReleaseStringUTFChars(args->nice_name, process);
    }

    void postAppSpecialize(const AppSpecializeArgs *) override {
        if (is_game) {
            std::thread hack_thread(hack_start, nullptr);
            hack_thread.detach();
        }
    }

private:
    Api *api = nullptr;
    JNIEnv *env = nullptr;
    bool is_game = false;
};

REGISTER_ZYGISK_MODULE(FreeFireMaxMod)
