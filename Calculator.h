#pragma once
#include <string>
#include "PluginManager.h"

class Calculator {
public:
    Calculator();
    void loadPlugins(const std::string& folder = "./plugins");
    double evaluate(const std::string& expression);

private:
    PluginManager plugins;
};