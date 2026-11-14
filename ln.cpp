#include <cmath>
#include <stdexcept>
#include "IPlugin.h"

const char* getFunctionName() {
    return "ln";
}

double calculate(double arg) {
    if (arg <= 0) throw std::runtime_error("ln от неположительного числа");
    return std::log(arg);
}