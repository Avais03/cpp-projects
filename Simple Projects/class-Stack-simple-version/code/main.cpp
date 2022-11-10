#include <iostream>
#include "stack.hpp"
signed main () {
    stack<int> rosbinik;
    while (true) {
        std::string s;
        std::cin >> s;
        if (s == "push") {
            int n;
            std::cin >> n;
            rosbinik.push(n);
            std::cout << "ok\n";
        }
        if (s == "pop") {
            if (!rosbinik.empty()) {
                std::cout << rosbinik.top() << '\n';
                rosbinik.pop();
            } else
                std::cout << "error\n";
        }
        if (s == "back") {
            if (!rosbinik.empty())
                std::cout << rosbinik.top() << '\n';
            else
                std::cout << "error\n";
        }
        if (s == "clear") {
            if (!rosbinik.empty())
                rosbinik.clear();
            std::cout << "ok\n";
        }
        if (s == "size_")
            std::cout << rosbinik.size() << '\n';
        if (s == "exit") {
            std::cout << "bye\n";
            break;
        }
    }
}