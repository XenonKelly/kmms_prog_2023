#pragma once

#include "menu.hpp"

namespace KLikhosherstova {

    // Логика расположения функций в отношении <1 функция> == <n элементов меню>
    //      - расположение вверху и по алфавиту
    const MenuItem* exit(const MenuItem* current);
    const MenuItem* go_back(const MenuItem* current);
    const MenuItem* show_menu(const MenuItem* current);

    // Логика расположения функций в отношении <1 функция> == <1 элемент меню>
    //      - повторяем такое же расположение как в меню
    const MenuItem* study_algebra(const MenuItem* current);
    const MenuItem* study_mathan(const MenuItem* current);

    const MenuItem* algebra_summ(const MenuItem* current);
    const MenuItem* algebra_substract(const MenuItem* current);
    const MenuItem* algebra_multiply(const MenuItem* current);
    const MenuItem* algebra_divide(const MenuItem* current);

    const MenuItem* mathan_diff(const MenuItem* current);
    const MenuItem* mathan_int(const MenuItem* current);
}
