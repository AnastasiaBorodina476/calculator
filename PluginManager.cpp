#include "PluginManager.h"
#include <iostream>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

using namespace std;
namespace fs = std::filesystem;

PluginManager::PluginManager() {}

PluginManager::~PluginManager() {
    for (auto lib : loadedLibs) {
#ifdef _WIN32
        FreeLibrary((HMODULE)lib);
#else
        dlclose(lib);
#endif
    }
}

void PluginManager::loadPlugins(const string& folder) {
    if (!fs::exists(folder)) {
        cout << "Папка " << folder << " не найдена\n";
        return;
    }
    for (auto& e : fs::directory_iterator(folder)) {
        string path = e.path().string();
#ifdef _WIN32
        if (e.path().extension() != ".dll") continue;
        HMODULE lib = LoadLibraryA(path.c_str());
        if (!lib) continue;
        auto getName = (const char* (*)())GetProcAddress(lib, "getFunctionName");
        auto calc = (double(*)(double))GetProcAddress(lib, "calculate");
#else
        if (e.path().extension() != ".so") continue;
        void* lib = dlopen(path.c_str(), RTLD_LAZY);
        if (!lib) continue;
        auto getName = (const char* (*)())dlsym(lib, "getFunctionName");
        auto calc = (double(*)(double))dlsym(lib, "calculate");
#endif
        if (!getName || !calc) {
            cout << "Некорректная dll: " << path << "\n";
#ifdef _WIN32
            FreeLibrary((HMODULE)lib);
#else
            dlclose(lib);
#endif
            continue;
        }
        string name = getName();
        functions[name] = calc;
        loadedLibs.push_back(lib);
        cout << "Загружено: " << name << "\n";
    }
}

bool PluginManager::hasFunction(const string& name) const {
    return functions.find(name) != functions.end();
}

double PluginManager::call(const string& name, double arg) const {
    return functions.at(name)(arg);
}