#include <iostream>
#include <string>
#include <clocale>
#include "Calculator.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    {
        Calculator calc;
        calc.loadPlugins("./plugins");

        string line;
        while (true) {
            cout << "> ";
            if (!getline(cin, line)) break;
            if (line == "exit") break;
            if (line.empty()) continue;
            try {
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
// Ветка dev готова к сдаче