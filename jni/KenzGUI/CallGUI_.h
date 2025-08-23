#pragma once 

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"

#include "Unity/Unity.h"
#include "Unity/Vector2.h"
#include "Unity/Vector3.h"
#include "Unity/Rect.h"
#include "Unity/Quaternion.h"

#include "ImGui/FONTS/DEFAULT.h"
#include "ImGui/Font.h"
#include "ImGui/Icon.h"
#include "ImGui/Iconcpp.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/ImGuiTheme.h"
#include "ImGui/backends/imgui_impl_opengl3.h"

#include "ByNameModding/Tools.h"
#include "ByNameModding/fake_dlfcn.h"
#include "ByNameModding/Il2Cpp.h"

#include "DobbyHook/dobby.h"
#include "Includes/Macros.h"
