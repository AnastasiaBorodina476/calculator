#include <cmath>
#include <stdexcept>
#include "IPlugin.h"

const char* getFunctionName() { 
    return "sqrt"; 
}

double calculate(double arg) {
    if (arg < 0) throw std::runtime_error("sqrt от отрицательного числа");
    return std::sqrt(arg);
}