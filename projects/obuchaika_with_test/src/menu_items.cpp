#include <cstddef>

#include "menu_items.hpp"
#include "menu_functions.hpp"


const KLikhosherstova::MenuItem KLikhosherstova::ALGEBRA_SUMM = {
    "1 - Хочу научиться складывать!", KLikhosherstova::algebra_summ, &KLikhosherstova::STUDY_ALGEBRA
};
const KLikhosherstova::MenuItem KLikhosherstova::ALGEBRA_SUBSTRACT = {
    "2 - Хочу научиться вычитать!", KLikhosherstova::algebra_substract, &KLikhosherstova::STUDY_ALGEBRA
};
const KLikhosherstova::MenuItem KLikhosherstova::ALGEBRA_MULTIPLY = {
    "3 - Хочу научиться умножать!", KLikhosherstova::algebra_multiply, &KLikhosherstova::STUDY_ALGEBRA
};
const KLikhosherstova::MenuItem KLikhosherstova::ALGEBRA_DIVIDE = {
    "4 - Хочу научиться делить!", KLikhosherstova::algebra_divide, &KLikhosherstova::STUDY_ALGEBRA
};
const KLikhosherstova::MenuItem KLikhosherstova::ALGEBRA_GO_BACK = {
    "0 - Вернуться к выбору предметов", KLikhosherstova::go_back, &KLikhosherstova::STUDY_ALGEBRA
};

namespace {
    const KLikhosherstova::MenuItem* const study_children_from_algebra[] = {
        &KLikhosherstova::ALGEBRA_GO_BACK,
        &KLikhosherstova::ALGEBRA_SUMM,
        &KLikhosherstova::ALGEBRA_SUBSTRACT,
        &KLikhosherstova::ALGEBRA_MULTIPLY,
        &KLikhosherstova::ALGEBRA_DIVIDE
    };
    const int study_children_from_algebra_size = sizeof(study_children_from_algebra) / sizeof(study_children_from_algebra[0]);
}

const KLikhosherstova::MenuItem KLikhosherstova::MATHAN_DIFF = {
    "1 - Хочу изучить дифференциальное исчисление!", KLikhosherstova::mathan_diff, &KLikhosherstova::STUDY_MATHAN
};
const KLikhosherstova::MenuItem KLikhosherstova::MATHAN_INT = {
    "2 - Хочу изучить интегральное исчисление!", KLikhosherstova::mathan_int, &KLikhosherstova::STUDY_MATHAN
};
const KLikhosherstova::MenuItem KLikhosherstova::MATHAN_GO_BACK = {
    "0 - Вернуться к выбору предметов", KLikhosherstova::go_back, &KLikhosherstova::STUDY_MATHAN
};

namespace {
    const KLikhosherstova::MenuItem* const study_children_from_mathan[] = {
        &KLikhosherstova::MATHAN_GO_BACK,
        &KLikhosherstova::MATHAN_DIFF,
        &KLikhosherstova::MATHAN_INT,
    };
    const int study_children_from_mathan_size = sizeof(study_children_from_mathan) / sizeof(study_children_from_mathan[0]);
}

const KLikhosherstova::MenuItem KLikhosherstova::STUDY_ALGEBRA = {
    "1 - Хочу изучать алгебру!", KLikhosherstova::show_menu, &KLikhosherstova::STUDY, study_children_from_algebra, study_children_from_algebra_size
};

const KLikhosherstova::MenuItem KLikhosherstova::STUDY_MATHAN = {
    "2 - Хочу изучать математический анализ!", KLikhosherstova::show_menu, &KLikhosherstova::STUDY, study_children_from_mathan, study_children_from_mathan_size
};

const KLikhosherstova::MenuItem KLikhosherstova::STUDY_GO_BACK = {
    "0 - Выйти в главное меню", KLikhosherstova::go_back, &KLikhosherstova::STUDY
};

namespace {
    const KLikhosherstova::MenuItem* const subject_children[] = {
        &KLikhosherstova::STUDY_GO_BACK, 
        &KLikhosherstova::STUDY_ALGEBRA,
        &KLikhosherstova::STUDY_MATHAN
    };
    const int subject_size = sizeof(subject_children) / sizeof(subject_children[0]);
}

const KLikhosherstova::MenuItem KLikhosherstova::STUDY = {
    "1 - Хочу учиться математике!", KLikhosherstova::show_menu, &KLikhosherstova::MAIN, subject_children, subject_size
};
const KLikhosherstova::MenuItem KLikhosherstova::EXIT = {
    "0 - Довольно математики!", KLikhosherstova::exit, &KLikhosherstova::MAIN
};

namespace {
    const KLikhosherstova::MenuItem* const main_children[] = {
        &KLikhosherstova::EXIT,
        &KLikhosherstova::STUDY
    };
    const int main_size = sizeof(main_children) / sizeof(main_children[0]);
}

const KLikhosherstova::MenuItem KLikhosherstova::MAIN = {
    nullptr, KLikhosherstova::show_menu, nullptr, main_children, main_size
};
