#include "Calculator.h"
#include "Parser.h"
#include <stdexcept>

Calculator::Calculator() {}

void Calculator::loadPlugins(const std::string& folder) {
    plugins.loadPlugins(folder);
}

double Calculator::evaluate(const std::string& expression) {
    auto caller = [this](const std::string& name, double arg) -> double {
        if (!plugins.hasFunction(name)) {
            throw std::runtime_error("Функция не найдена: " + name);
        }
        return plugins.call(name, arg);
        };

    Parser p(expression, caller);

    return p.parse();
}