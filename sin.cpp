#include <cmath>
#include <numbers>
#include "IPlugin.h"

const char* getFunctionName() {
    return "sin";
}

double calculate(double arg) {
    return std::sin(arg * std::numbers::pi / 180.0);
}