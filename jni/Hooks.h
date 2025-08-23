#pragma once

// Free Fire Max specific toggles and variables
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

// Feature toggles
bool Dummytoggle1 = false;
bool Dummytoggle2 = false;
bool Dummytoggle3 = false;
bool Dummytoggle4 = false;
bool Dummytoggle5 = false;
bool Dummytoggle6 = false;
bool Dummytoggle7 = false;
bool Dummytoggle8 = false;  // No Recoil
bool Dummytoggle9 = false;  // No Spread
bool Dummytoggle10 = false; // High FOV
bool Dummytoggle11 = false; // Speed Hack
bool Dummytoggle12 = false; // God Mode
bool Dummytoggle13 = false; // Unlimited Ammo
bool Dummytoggle14 = false; // Fast Run
bool Dummytoggle15 = false; // Jump Hack
bool Dummytoggle16 = false;
bool Dummytoggle17 = false;
bool Dummytoggle18 = false;
bool Dummytoggle19 = false;
bool Dummytoggle20 = false;

// Currency/Diamonds hook
bool IsIntExample2 = false; // Unlimited Diamonds toggle
int (*old_IntExample2)(void *instance);
int IntExample2(void *instance) {
	if (instance != NULL) {
		if (IsIntExample2) {
			return 999999; // Unlimited diamonds
		}
	}
	return old_IntExample2(instance);
}

// Free Fire specific offsets from CS file
#define HEALTH_OFFSET 0x7b45840
#define AMMO_OFFSET 0x7c25b54
#define CURRENCY_OFFSET 0x25ffe14
#define PLAYER_CONTROLLER_OFFSET 0x8800054
#define SPEED_OFFSET 0x7c25ce0
#define RECOIL_OFFSET 0x7c25d74
#define FOV_OFFSET 0x7c25e40

// Additional Free Fire Max offsets extracted from CS file
#define AMMO_LEFT_OFFSET 0x7c89b98
#define HEALTH_GET_OFFSET 0x245576
#define AMMO_CAPACITY_OFFSET 0x232574
#define PLAYER_POSITION_OFFSET 0x7c25b5c