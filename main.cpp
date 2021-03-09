#include <iostream>

#include "big_integer.hpp"

using namespace NBigInt;

int main() {
    std::ios_base::sync_with_stdio(false);           // ускоренный ввод-вывод
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    TBint a, b;
    char action;
    while (std::cin >> a >> b >> action) {
        if (action == '+') {
            std::cout << a + b << '\n';
        } else if (action == '-') {
            if (a < b) {
                std::cout << "Error\n";
                continue;
            } else {
                std::cout << a - b << '\n';
            }
        } else if (action == '=') {
            std::cout << std::boolalpha << (a == b) << '\n';
        } else if (action == '<') {
            std::cout << std::boolalpha << (a < b) << '\n';
        } else if (action == '>') {
            std::cout << std::boolalpha << (a > b) << '\n';
        } else if (action == '/') {
            if (b == 0) {
                std::cout << "Error\n";
                continue;
            }
            std::cout <<  a / b << '\n';
        } else if (action == '*') {
            std::cout << a * b << '\n';
        } else if (action == '^') {
            if ( b == 0 && a == 0 ){
                std::cout << "Error\n";
                continue;
            }
            std::cout << pow(a, b) << '\n';
        } else {
            std::cout << "Error\n";
        }
    }

    return 0;
}