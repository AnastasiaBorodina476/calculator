#pragma once
#include <string>
#include <functional>

class Parser {
public:
    // Лямбда, которая будет вызывать плагины
    using PluginCaller = std::function<double(const std::string&, double)>;

    Parser(const std::string& s, PluginCaller caller);
    double parse();

private:
    std::string s;
    size_t pos;
    PluginCaller callPlugin;

    void skip();
    double expr();
    double term();
    double factor();
    double primary();
}; // <--- ВАЖНО: вот эта точка с запятой!