#include <iostream>
#include <string>
#include <clocale>
#include "Calculator.h" // <--- Меняем Parser на Calculator

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "=== Калькулятор с плагинами (C++20) ===\n";

    {
        Calculator calc; // <--- Создаем Калькулятор
        calc.loadPlugins("./plugins"); // <--- Он внутри себя загрузит плагины

        string line;
        while (true) {
            cout << "> ";
            if (!getline(cin, line)) break;
            if (line == "exit") break;
            if (line.empty()) continue;
            try {
                // Передаем строку в Калькулятор, а не в Парсер напрямую
                cout << "= " << calc.evaluate(line) << "\n";
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << "\n";
            }
        }
    }

    cout << "Выход из программы.\n";
    return 0;
}