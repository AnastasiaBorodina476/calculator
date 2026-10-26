#pragma once
#include <string>
#include <map>
#include <vector>

class PluginManager {
public:
    PluginManager();
    ~PluginManager();

    void loadPlugins(const std::string& folder = "./plugins");
    bool hasFunction(const std::string& name) const;
    double call(const std::string& name, double arg) const;

private:
    std::map<std::string, double(*)(double)> functions;
    std::vector<void*> loadedLibs;
};