#include <clocale>
#include <iostream>

#include "menu.hpp"
#include "menu_items.hpp"
#include "menu_functions.hpp"


int main() {
    std::setlocale(LC_ALL, "");
    std::cout << "Здравствуй, дорогой пользователь" << std::endl;

    const KLikhosherstova::MenuItem* current = &KLikhosherstova::MAIN;
    do {
        current = current->func(current);
    } while (true);
}
