#include "Parser.h"
#include <cctype>
#include <stdexcept>
#include <cmath>
#include <numbers>

using namespace std;

Parser::Parser(const string& str, PluginCaller caller)
    : s(str), pos(0), callPlugin(caller) {}

void Parser::skip() {
    while (pos < s.size() && isspace(s[pos])) pos++;
}

double Parser::parse() {
    double r = expr();
    skip();
    if (pos != s.size()) throw runtime_error("Лишние символы");
    return r;
}

double Parser::expr() {
    double r = term();
    while (true) {
        skip();
        if (pos < s.size() && (s[pos] == '+' || s[pos] == '-')) {
            char op = s[pos++];
            double rhs = term();
            r = (op == '+') ? r + rhs : r - rhs;
        }
        else break;
    }
    return r;
}

double Parser::term() {
    double r = factor();
    while (true) {
        skip();
        if (pos < s.size() && (s[pos] == '*' || s[pos] == '/')) {
            char op = s[pos++];
            double rhs = factor();
            if (op == '/' && rhs == 0) throw runtime_error("Деление на ноль");
            r = (op == '*') ? r * rhs : r / rhs;
        }
        else break;
    }
    return r;
}

double Parser::factor() {
    skip();
    if (pos < s.size() && s[pos] == '-') {
        pos++;
        return -factor();
    }
    return primary();
}

double Parser::primary() {
    skip();
    if (pos >= s.size()) throw runtime_error("Конец выражения");

    if (s[pos] == 'e' && (pos + 1 == s.size() || !isalnum(s[pos + 1]))) {
        pos++; return std::numbers::e;
    }
    if (s.compare(pos, 2, "pi") == 0) {
        pos += 2; return std::numbers::pi;
    }

    if (s[pos] == '(') {
        pos++;
        double v = expr();
        skip();
        if (pos >= s.size() || s[pos] != ')') throw runtime_error("Ожидалась ')'");
        pos++;
        return v;
    }

    if (isdigit(s[pos]) || s[pos] == '.') {
        size_t start = pos;
        while (pos < s.size() && (isdigit(s[pos]) || s[pos] == '.')) pos++;
        return stod(s.substr(start, pos - start));
    }

    if (isalpha(s[pos])) {
        size_t start = pos;
        while (pos < s.size() && (isalnum(s[pos]) || s[pos] == '_')) pos++;
        string name = s.substr(start, pos - start);
        skip();
        if (pos >= s.size() || s[pos] != '(') throw runtime_error("Ожидалась '('");
        pos++;
        double arg = expr();
        skip();
        if (pos >= s.size() || s[pos] != ')') throw runtime_error("Ожидалась ')'");
        pos++;

        return callPlugin(name, arg);
    }
    throw runtime_error("Неизвестный символ");
}