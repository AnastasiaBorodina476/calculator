#pragma once

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif

extern "C" {
    EXPORT const char* getFunctionName();
    EXPORT double calculate(double arg) noexcept(false);
}