#include <cmath>
#include <numbers>
#include "IPlugin.h"

const char* getFunctionName() { return "deg"; }
double calculate(double arg) {
    return arg * 180.0 / std::numbers::pi;
}