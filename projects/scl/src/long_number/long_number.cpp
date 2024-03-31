#include <iostream>                       
#include <cmath> 
#include <cstring>
#include "long_number.hpp"

using KLikhosherstova::LongNumber;



LongNumber::LongNumber() : length(1), sign(POSITIVE) {
    numbers = new int[length];
    numbers[0] = 0;
}

LongNumber::LongNumber(int value) {
    sign = (value >= 0) ? POSITIVE : NEGATIVE;
    value = std::abs(value);
    length = (value == 0) ? 1 : get_length(value);
    numbers = new int[length];
    for (int i = 0; i < length; i++) {
        numbers[i] = value % 10;
        value /= 10;
    }
}

LongNumber::LongNumber(const char* const str) {
    int str_length = get_length(str);
    if (str[0] == MINUS) {
        sign = -1;
        length = str_length - 1;
    }
    else {
        sign = 1;
        length = str_length;
    }

    numbers = new int[length];
    for (int i = 0; i < length; i++) {
        numbers[i] = str[str_length - i - 1] - ZERO;
    }
}

LongNumber::LongNumber(const LongNumber& x) {
    length = x.length;
    sign = x.sign;
    numbers = new int[length];
    for (int i = 0; i < length; i++) {
        numbers[i] = x.numbers[i];
    }
}

LongNumber::LongNumber(LongNumber&& x) {
    length = x.length;
    sign = x.sign;
    numbers = x.numbers;
    x.numbers = nullptr;
}

LongNumber::~LongNumber() {
    length = 0;
    delete[] numbers;
    numbers = nullptr;
}


LongNumber& LongNumber::operator = (const char* const str) {
    int str_length = get_length(str);
    if (str[0] == MINUS) {
        sign = -1;
        length = str_length - 1;
    }
    else {
        sign = 1;
        length = str_length;
    }

    delete[] numbers;
    numbers = new int[length];
    for (int i = 0; i < length; i++) {
        numbers[i] = str[str_length - i - 1] - ZERO;
    }

    return *this;
}

LongNumber& LongNumber::operator = (int value) {
    sign = (value >= 0) ? POSITIVE : NEGATIVE;
    value = std::abs(value);
    length = (value == 0) ? 1 : get_length(value);
    numbers = new int[length];

    for (int i = 0; i < length; i++) {
        numbers[i] = value % 10;
        value /= 10;
    }

    return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
    if (this == &x) return *this;

    length = x.length;
    sign = x.sign;

    delete[] numbers;
    numbers = new int[length];
    for (int i = 0; i < length; i++) {
        numbers[i] = x.numbers[i];
    }

    return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
    length = x.length;
    sign = x.sign;

    delete[] numbers;
    numbers = x.numbers;
    x.numbers = nullptr;

    return *this;
}



bool LongNumber::operator == (const LongNumber& x) const {
    if ((sign != x.sign) || (length != x.length)) { return false; }

    else {
        int a = std::abs(to_int(*this));
        int b = std::abs(to_int(x));
        while ((a > 0) || (b > 0)) {
            if (a % 10 != b % 10) {
                return false;
            }
            a /= 10;
            b /= 10;
        }
        return true;
    }
}

bool LongNumber::operator != (const LongNumber& x) const { return !operator==(x); }

bool LongNumber::operator > (const LongNumber& x) const {

    if (operator==(x)) { return false; }

    int a = reverse_digits(std::abs(to_int(*this)));
    int b = reverse_digits(std::abs(to_int(x)));

    if (sign > x.sign) { return true; }
    else if (sign < x.sign) { return false; }
    else if (((sign < 0) && (length < x.length)) || ((sign > 0) && (length > x.length))) { return true; }
    else if (((sign < 0) && (length > x.length)) || ((sign > 0) && (length < x.length))) { return false; }
    else {
        while ((a > 0) || (b > 0)) {
            if (a % 10 < b % 10) { return sign < 0; }
            else if (a % 10 > b % 10) { return sign > 0; }
            a /= 10;
            b /= 10;
        }
        return false;
    }
}

bool LongNumber::operator < (const LongNumber& x) const { return !operator>(x); }

LongNumber LongNumber::operator + (const LongNumber& x) const {
    if ((sign < 0) && (x.sign > 0)) {
        int a_int = std::abs(to_int(*this));
        LongNumber a(a_int);

        int b_int = std::abs(to_int(x));
        LongNumber b(b_int);

        LongNumber result(to_int(b.operator-(a)));
        return result;
    }

    else if ((sign > 0) && (x.sign < 0)) {
        int b_int = std::abs(to_int(x));
        LongNumber b(b_int);
        LongNumber result(operator-(b));
        return result;
    }

    else {
        int summ = 0;
        int a = std::abs(to_int(*this));
        int b = std::abs(to_int(x));
        int total_length = std::max(length, x.length);
        int i = 0;
        while (i < total_length) {
            summ += (int)((((a % 10) + (b % 10)) * pow(10, i)));
            a /= 10;
            b /= 10;
            i++;
        }

        LongNumber result(summ * (sign));
        return result;
    }  
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
    if (((sign < 0) && (x.sign > 0)) || ((sign > 0) && (x.sign < 0))) {  
        int a_int = std::abs(to_int(*this));
        LongNumber a(a_int);

        int b_int = std::abs(to_int(x));
        LongNumber b(b_int);

        LongNumber result(to_int(a.operator+(b)));
        return result;
    }

    else if (sign < 0 && x.sign < 0) {
        int a_int = std::abs(to_int(*this));
        LongNumber a(a_int);

        int b_int = std::abs(to_int(x));
        LongNumber b(b_int);

        LongNumber result(to_int(b.operator-(a)));
        return result;
    }

    else {
        int diff = 0;
        int a = std::abs(to_int(*this));
        int b = std::abs(to_int(x));
        int total_length = std::max(length, x.length);
        int i = 0;

        while (i < total_length) {
            diff += (int)((((a % 10) - (b % 10)) * pow(10, i)));
            a /= 10;
            b /= 10;
            i++;
        }

        LongNumber result(diff * sign);
        return result;
    }
}


LongNumber LongNumber::operator * (const LongNumber& x) const {
    int product = 0;
    int a = std::abs(to_int(*this));
    int b = std::abs(to_int(x));
    int total_length = std::max(length, x.length);
    int i = 0;
    int k = 1;

    while ((i < total_length) && (k <= total_length)) { 
        product += (((a * (b % (int)pow(10, k))) * pow(10, i)));
        b /= 10;
        i++;
    }
    int sign_res = sign == x.sign ? POSITIVE : NEGATIVE;
    LongNumber result(product * sign_res);
    return result;
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
    int quotient = 0;
    int result_sign;
    int a = std::abs(to_int(*this));
    int b = std::abs(to_int(x));

    if (length < x.length) {
        LongNumber result(0);
        return result;
    }
    else if (a == b) {
        result_sign = sign == x.sign ? POSITIVE : NEGATIVE;
        LongNumber result(1 * result_sign);
        return result;
    }

    else {
        int main_point = a / pow(10, length - x.length) >= b ? pow(10, length - x.length) : pow(10, length - x.length - 1);
        int digits_before_point = get_length(a / main_point);
        int digits_after_point = length - digits_before_point;
        int* tmp = new int[digits_after_point + 1];

        for (int i = 0; i < digits_after_point; i++) {
            tmp[i] = 0;
        }

        int number = a;
        int j = 1;

        while (number != (a / main_point))
        {
            int digit = number % 10;
            number /= 10;
            tmp[j] = digit;
            j++;
        }

        int k = digits_after_point;
        int i = a / pow(10, length - x.length) >= b ? length - x.length : length - x.length - 1; 
        quotient += (a / main_point / b) * pow(10, i); 
        i--;

        int tmp_int = ((a / main_point) - (((a / main_point) / b) * b)) * 10 + tmp[k];
        k--;
        while ((i >= 0)) {

            if (tmp_int / b <= 0) {  
                i--;
                tmp_int = tmp_int * 10 + tmp[k];
                quotient += (tmp_int / b) * pow(10, i);
                i--;
                k--;
                tmp_int = (tmp_int - (tmp_int / b) * b) * 10 + tmp[k];
            }
            else {
                quotient += (tmp_int / b) * pow(10, i);
                i--;
                tmp_int = (tmp_int - (tmp_int / b) * b) * 10 + tmp[k];
                k--;
            }
        }

        result_sign = sign == x.sign ? POSITIVE : NEGATIVE;
        LongNumber result(quotient * result_sign);
        delete[] tmp;
        return result;
    }
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
    LongNumber q, r;

    int a_int = std::abs(to_int(*this));
    LongNumber a(a_int);

    int b_int = std::abs(to_int(x));
    LongNumber b(b_int);

    q = a.operator/(b); 

    if ((sign == POSITIVE) && (x.sign == POSITIVE) || ((sign == POSITIVE) && (x.sign == NEGATIVE))) {
        r = a.operator-(q.operator*(b));
    }
    else if ((sign == NEGATIVE) && (x.sign == POSITIVE)) {
        q.sign = NEGATIVE;
        q = to_int(q) - 1;
        q.length = get_length(to_int(q));
        r = operator-(q.operator*(x));
    }
    else {
        q.sign = POSITIVE;
        q = to_int(q) + 1;
        q.length = get_length(to_int(q));
        r = operator-(q.operator*(x));
    }
    return r;
}

//вспомогательные функции
int LongNumber::get_length(int x) const {
    return ((bool)x * (int)log10(std::abs(x)) + 1);
}

int LongNumber::get_length(const char* const str) const {
    if (!str) return 0;

    int length = 0;
    while (str[length] != END) {
        length++;
    }

    return length;
}

bool LongNumber::is_negative() const {
	return sign == NEGATIVE;
}

int LongNumber::reverse_digits(int num) const {
    int rev_num = 0;
    while (num > 0) {
        rev_num = rev_num * 10 + num % 10;
        num = num / 10;
    }
    return rev_num;
}

int LongNumber::to_int(const LongNumber& x) const {
    int result = 0;
    int i = 0;
    while (i < x.length) {
        result += x.numbers[i] * pow(10, i);
        i++;
    }
    return (x.sign == POSITIVE) ? result : (-1) * result;
}


// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace KLikhosherstova {
    std::ostream& operator << (std::ostream& os, const LongNumber& x) {
        if (x.sign == LongNumber::NEGATIVE) {
            os << LongNumber::MINUS;
        }
        for (int i = 0; i < x.length; i++) {
            os << x.numbers[x.length - i - 1];
        }
        return os;
    }
}
