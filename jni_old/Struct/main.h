#ifndef MAIN_H
#define MAIN_H

#include <map>
#include <string>
#include <Struct/tools.hpp>

typedef unsigned long DWORD;
struct Config_t {
    struct {
        bool Line = false;
        bool Box = false;
        bool Target = false;
    } ESP;
};

struct Config_t Config;

typedef unsigned long ulong;
inline pid_t pid = 0;

typedef unsigned long DWORD;
static uintptr_t libBase;

// FontAwesome Icons for Enhanced GUI
#define ICON_FA_GAMEPAD "\xef\x84\x9b"  // 
#define ICON_FA_EYE "\xef\x81\xae"      // 
#define ICON_FA_BARS "\xef\x83\x89"     // 
#define ICON_FA_COGS "\xef\x85\x93"     // 

// Enhanced feature variables
static bool Enhanced_Theme_Enabled = false;
static int Theme_Selection = 0;

inline std::map < std::string, void*> _methods;
inline std::map < std::string, size_t > _fields;

template<typename T>
inline T getFieldValue(void *instance,ulong offset) {
    return *(T*)((uintptr_t)instance + offset);
}

template<typename T>
inline T setFieldValue(void *instance,ulong offset, T value) {
    *(T*)((uintptr_t)instance + offset) = value;
}

void menu();
void *getRealAddr(ulong offset);

#endif //MAIN_H
