#include <cstdlib>
#include<iostream>
#include <random>

#include "menu_functions.hpp"

// Вспомогательные функции для этой единицы трансляции должны быть объявлены 
// внутри этой единицы трансляции (хедер не является единицей трансляции) 
// в анонимном namespace. Тогда при объединении линкером всех имён в один файл 
// не будет конфликта. И располагаем их по алфавиту.
namespace {
    int calculate_divide(const int a, const int b);
    int calculate_multiply(const int a, const int b);
    int calculate_summ(const int a, const int b);
    int calculate_substract(const int a, const int b);
    const KLikhosherstova::MenuItem* choose_continuation(const KLikhosherstova::MenuItem* option);
    const KLikhosherstova::MenuItem* execute_operation(
        const KLikhosherstova::MenuItem* current,
        const char *const operation,
        int (*calculate)(const int a, const int b)
    );
    int get_random_number();
}

// Логика расположения функций в отношении <1 функция> == <n элементов меню>
//      - расположение вверху и по алфавиту
const KLikhosherstova::MenuItem* KLikhosherstova::go_back(const MenuItem* current) {
    return current->parent->parent;
}

const KLikhosherstova::MenuItem* KLikhosherstova::exit(const MenuItem* current) {
	std::exit(0);
}

const KLikhosherstova::MenuItem* KLikhosherstova::show_menu(const MenuItem* current) {
    for (int i = 1; i < current->children_count; i++) {
        std::cout << current->children[i]->title << std::endl;
    }
    std::cout << current->children[0]->title << std::endl;
    std::cout << "Выберите действие >> ";

    int user_input;
    std::cin >> user_input;
    std::cout << std::endl;

    return current->children[user_input];
}

// Логика расположения функций в отношении <1 функция> == <1 элемент меню>
//      - повторяем такое же расположение как в меню
const KLikhosherstova::MenuItem* KLikhosherstova::study_algebra(const MenuItem* current) {
    return current->parent;
}

const KLikhosherstova::MenuItem* KLikhosherstova::study_mathan(const MenuItem* current) {
    std::cout << current->title << std::endl << std::endl;
    return current->parent;
}

const KLikhosherstova::MenuItem* KLikhosherstova::algebra_summ(const MenuItem* current) {
    return execute_operation(current, " + ", calculate_summ);
}

const KLikhosherstova::MenuItem* KLikhosherstova::algebra_substract(const MenuItem* current) {
    return execute_operation(current, " - ", calculate_substract);
}

const KLikhosherstova::MenuItem* KLikhosherstova::algebra_multiply(const MenuItem* current) {
    return execute_operation(current, " * ", calculate_multiply);
}

const KLikhosherstova::MenuItem* KLikhosherstova::algebra_divide(const MenuItem* current) {
    return execute_operation(current, " / ", calculate_divide);
}

const KLikhosherstova::MenuItem* KLikhosherstova::mathan_diff(const MenuItem* current) {
    return current->parent;
}

const KLikhosherstova::MenuItem* KLikhosherstova::mathan_int(const MenuItem* current) {
    return current->parent;
}

namespace {
    int calculate_divide(const int a, const int b) {
        return a / b;
    }

    int calculate_multiply(const int a, const int b) {
        return a * b;
    }

    int calculate_summ(const int a, const int b) {
        return a + b;
    }

    int calculate_substract(const int a, const int b) {
        return a - b;
    }

    const KLikhosherstova::MenuItem* choose_continuation(const KLikhosherstova::MenuItem* option) {
        std::cout << "Хотите продолжить?" << std::endl;
        std::cout << "1 - Хочу продолжить решать примеры этой категории" << std::endl;
        std::cout << "0 - Выйти в меню" << std::endl;

        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1:
                return option;
                break;
            case 0:
                return option->parent;
                break;
        }
        return option;
    }

    const KLikhosherstova::MenuItem* execute_operation(
        const KLikhosherstova::MenuItem* current,
        const char *const operation,
        int (*calculate)(const int a, const int b)
    ) {
        int quotient;
        int a = get_random_number();
        int b = get_random_number();
        std::cout << "Сколько будет " << a << operation << b << " = ";
        std::cin >> quotient;
        while (quotient != calculate(a, b)) {
            std::cout << "Неверный ответ! Попробуйте снова" << std::endl;
            std::cin >> quotient;
        }
        return choose_continuation(current);
    }

    int get_random_number() {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> num(10, 50);

        return num(rng);
    }
}
