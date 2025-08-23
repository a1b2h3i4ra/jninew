#ifndef DRAWMENU
#define DRAWMENU


void SetGUI() {
    ImGui::CreateContext();

    // Display size
    ImGuiIO& io = ImGui::GetIO();
    int(*get_width)(void*);
    int(*get_height)(void*);
    get_width = (int (*)(void*)) (Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Screen"), OBFUSCATE("get_width"), 0));
    get_height = (int (*)(void*)) (Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Screen"), OBFUSCATE("get_height"), 0));
    io.DisplaySize = ImVec2((float)get_width(0), (float)get_height(0));
	
    ImGui::StyleColorsDark(); // Set a theme
	ImGuiStyle *style = &ImGui::GetStyle();
	style->WindowTitleAlign = ImVec2(0.5, 0.5);
	style->PopupRounding = 3;
    style->WindowPadding = ImVec2(4, 4);
    style->FramePadding  = ImVec2(2, 2);
    style->ItemSpacing   = ImVec2(2, 2);
    style->ScrollbarSize = 17;
    style->WindowBorderSize = 3;
    style->ChildBorderSize  = 1;
    style->PopupBorderSize  = 1;
    style->FrameBorderSize  = 1;
    style->WindowRounding    = 3;
    style->ChildRounding     = 3;
    style->FrameRounding     = 3;
    style->ScrollbarRounding = 2;
    style->GrabRounding      = 3;
	ImGui::GetStyle().Alpha = 1.0f;
	
	style->Colors[ImGuiCol_Text]                   = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled]           = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	style->Colors[ImGuiCol_WindowBg]               = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
	style->Colors[ImGuiCol_ChildBg]                = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
	style->Colors[ImGuiCol_PopupBg]                = ImVec4(0.15f, 0.15f, 0.15f, 0.95f);
	style->Colors[ImGuiCol_Border]                 = ImVec4(0.25f, 0.25f, 0.25f, 0.60f);
	style->Colors[ImGuiCol_FrameBg]                = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive]          = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
	style->Colors[ImGuiCol_TitleBg]                = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
	style->Colors[ImGuiCol_TitleBgActive]          = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg]              = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.12f, 0.12f, 0.12f, 0.39f);
	style->Colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.33f, 0.47f, 0.64f, 0.50f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.33f, 0.47f, 0.64f, 0.70f);
	style->Colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.33f, 0.47f, 0.64f, 1.00f);
	style->Colors[ImGuiCol_CheckMark]              = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
	style->Colors[ImGuiCol_SliderGrab]             = ImVec4(0.33f, 0.47f, 0.64f, 1.00f);
	style->Colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.33f, 0.47f, 0.64f, 1.00f);
	style->Colors[ImGuiCol_Button]                 = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered]          = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style->Colors[ImGuiCol_ButtonActive]           = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style->Colors[ImGuiCol_Header]                 = ImVec4(0.25f, 0.35f, 0.50f, 0.60f);
	style->Colors[ImGuiCol_HeaderHovered]          = ImVec4(0.33f, 0.47f, 0.64f, 0.80f);
	style->Colors[ImGuiCol_HeaderActive]           = ImVec4(0.33f, 0.47f, 0.64f, 1.00f);
	style->Colors[ImGuiCol_Separator]              = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style->Colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.33f, 0.47f, 0.64f, 0.70f);
	style->Colors[ImGuiCol_SeparatorActive]        = ImVec4(0.33f, 0.47f, 0.64f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip]             = ImVec4(0.33f, 0.47f, 0.64f, 0.25f);
	style->Colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.33f, 0.47f, 0.64f, 0.70f);
	style->Colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.33f, 0.47f, 0.64f, 1.00f);
	style->Colors[ImGuiCol_Tab]                    = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
	style->Colors[ImGuiCol_TabHovered]             = ImVec4(0.33f, 0.47f, 0.64f, 0.60f);
	style->Colors[ImGuiCol_TabActive]              = ImVec4(0.25f, 0.35f, 0.50f, 1.00f);
	style->Colors[ImGuiCol_TabUnfocused]           = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
	style->Colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

	
    ImGui_ImplOpenGL3_Init("#version 100"); // Open GL version
    
    io.IniFilename = NULL;     
    static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
    ImFontConfig icons_config;  
    ImFontConfig CustomFont;
    CustomFont.FontDataOwnedByAtlas = false;

    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.OversampleH = 2.5;
    icons_config.OversampleV = 2.5;

    io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Custom), sizeof(Custom), 32.0f, &CustomFont);
    io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 32.0f, &icons_config, icons_ranges);
    
    ImFontConfig font_cfg;
    font_cfg.SizePixels = 32.0f;
    io.Fonts->AddFontDefault(&font_cfg);
    ImGui::GetStyle().ScaleAllSizes(3.0f);
}

bool clearMousePos = true, setup = false;
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
    float m_fRadiusVariance;
    float m_AltitudeAngle;
    float m_AzimuthAngle;
};





#endif

