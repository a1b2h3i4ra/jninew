#pragma once
#include <KittyMemory.h>
#include <KittyUtils.h>

//Hook Utils
static unsigned long FindLibrary(const char *library) {
  char filename[0xFF] = {0},
       buffer[1024] = {0};
  FILE *fp = NULL;
  unsigned long address = 0;

  sprintf(filename, "/proc/%d/maps", getpid());

  fp = fopen(filename, "rt");
  if (fp == NULL) {
    goto done;
  }

  while (fgets(buffer, sizeof(buffer), fp)) {
    if (strstr(buffer, library)) {
      address = strtoul(buffer, NULL, 16);
      if (address == 0x8000)
        address = 0;
      break;
    }
  }

  done:

  if (fp) {
    fclose(fp);
  }

  return address;
}

uint32_t FindPattern(const char *lib, const char* bytes) {
    return  KittyMemory::findIdaPatternAddress(lib, bytes);
}

uint64_t get_module_base(pid_t pid, const char *module_name) {
    FILE *fp;
    uint64_t addr = 0;
    char *pch;
    char filename[32];
    char line[512];

    snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);

    fp = fopen(filename, "r");

    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, module_name)) {
                pch = strtok(line, "-");
                addr = strtoull(pch, NULL, 16);

                if (addr == 0x8000)
                    addr = 0;

                break;
            }
        }
        fclose(fp);
    }
    return addr;
}

// ===== ENHANCED TOOLS FROM NEW JNI =====
#include <Dobby/dobby.h>

namespace Tools {
    void Hook(void *target, void *replace, void **backup) {
        DobbyHook(target, replace, backup);
    }
    
    bool Read(void *addr, void *buffer, size_t length) {
        return KittyMemory::memRead(addr, buffer, length);
    }
    
    bool Write(void *addr, void *buffer, size_t length) {
        return KittyMemory::memWrite(addr, buffer, length);
    }
    
    bool ReadAddr(void *addr, void *buffer, size_t length) {
        return KittyMemory::memRead2(addr, buffer, length);
    }
    
    bool WriteAddr(void *addr, void *buffer, size_t length) {
        return KittyMemory::memWrite2(addr, buffer, length);
    }

    bool PVM_ReadAddr(void *addr, void *buffer, size_t length) {
        return KittyMemory::pvm_readv(addr, buffer, length);
    }
    
    bool PVM_WriteAddr(void *addr, void *buffer, size_t length) {
        return KittyMemory::pvm_writev(addr, buffer, length);
    }

    bool IsPtrValid(void *addr) {
        return KittyMemory::isValidAddress(addr);
    }

    uintptr_t GetBaseAddress(const char *name) {
        return KittyMemory::getLibraryBaseAddress(name);
    }
    
    uintptr_t GetEndAddress(const char *name) {
        return KittyMemory::getLibraryEndAddress(name);
    }
    
    uintptr_t FindPattern(const char *lib, const char* pattern) {
        return KittyMemory::findIdaPatternAddress(lib, pattern);
    }

    std::string RandomString(const int len) {
        std::string tmp_s;
        static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        
        srand((unsigned) time(NULL) * getpid());

        tmp_s.reserve(len);

        for (int i = 0; i < len; ++i) 
            tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
        
        return tmp_s;
    }
    
    std::string GetPackageName(JNIEnv *env, jobject context) {
        jclass contextClass = env->FindClass("android/content/Context");
        jmethodID getPackageNameMethod = env->GetMethodID(contextClass, "getPackageName", "()Ljava/lang/String;");
        jstring packageNameString = (jstring) env->CallObjectMethod(context, getPackageNameMethod);
        const char *packageName = env->GetStringUTFChars(packageNameString, 0);
        std::string result(packageName);
        env->ReleaseStringUTFChars(packageNameString, packageName);
        return result;
    }
}
// ===== END ENHANCED TOOLS =====
