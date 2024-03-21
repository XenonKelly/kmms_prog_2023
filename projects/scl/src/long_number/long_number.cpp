#include <iostream>                       
#include <cmath> 
#include <cstring>
#include "long_number.hpp"

using KLikhosherstova::LongNumber;



LongNumber::LongNumber() {
	numbers = new int;
	*numbers = 0;
	length = 1; 
	sign = POSITIVE;
}

LongNumber::LongNumber(const char* const str) {
	numbers = new int;
	*numbers = atoi(str);

	if (*str == MINUS) {
		length = strlen(str) - 1; //не видит функцию strlen (возможно, реализовать вручную)
		sign = NEGATIVE;
	}
	else {
		length = strlen(str);
		sign = POSITIVE;
	}
}

LongNumber::LongNumber(const LongNumber& x) {
	length = x.length;
	sign = x.sign;
	numbers = new int;
	*numbers = *x.numbers;
}

LongNumber::LongNumber(LongNumber&& x) : numbers(x.numbers), length(x.length), sign(x.sign) {
	x.numbers = nullptr;
	length = 0;
	sign = POSITIVE;
}

LongNumber::~LongNumber() {
    if (numbers != nullptr) {
        length = 0;
        delete numbers;
        numbers = nullptr;
    }
    else
        std::cout << "No data" << std::endl;
}

LongNumber& LongNumber::operator = (const char* const str) {
    if (numbers)
        delete numbers;

    length = strlen(str);
    numbers = new int;
    *numbers = atoi(str);

    if (*str == MINUS)
        sign = NEGATIVE;
    else
        sign = POSITIVE;

    return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
    if (this == &x)
        return *this;
    else {
        length = x.length;
        sign = x.sign;
        delete numbers;
        numbers = new int;
        for (int i = 0; i < length; i++) {
            numbers = x.numbers;
        }
    }
    return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
    if (&x != this) {
        delete numbers;
        numbers = x.numbers;
        length = x.length;
        sign = x.sign;
        x.numbers = nullptr;
        x.length = 0;
        x.sign = POSITIVE;
    }
    return *this;
}

bool LongNumber::operator == (const LongNumber& x) {
    if ((sign != x.sign) || (length != x.length)) { return false; }

    else {
        int a = abs(*numbers);
        int b = abs(*x.numbers);
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

bool LongNumber::operator != (const LongNumber& x) { return !operator==(x); }

bool LongNumber::operator > (const LongNumber& x) {

    if (operator==(x)) { return false; }

    int a = reverse_digits(abs(*numbers));
    int b = reverse_digits(abs(*x.numbers));

    if (sign > x.sign) { return true; }
    else if (sign < x.sign) { return false; }
    else if (((sign < 0) && (length < x.length)) || ((sign > 0) && (length > x.length))) { return true; }
    else if (((sign < 0) && (length > x.length)) || ((sign > 0) && (length < x.length))) { return false; }
    else {
        while ((a > 0) || (b > 0)) {
            if (a % 10 < b % 10) {
                return (sign < 0);
            }
            else if (a % 10 > b % 10) { return (sign > 0); }
            a /= 10;
            b /= 10;
        }
    }
}


bool LongNumber::operator < (const LongNumber& x) { return !operator>(x); }


LongNumber LongNumber::operator + (const LongNumber& x) {
    LongNumber result;
    if (sign != x.sign) { return operator-(x); }
    int a = abs(*numbers); 
    int b = abs(*x.numbers);
    int total_length = std::max(length, x.length);
    int i = 0;
    while (i < total_length) {
        *result.numbers += (int)((((a % 10) + (b % 10)) * pow(10, i)) * (sign));
        a /= 10;
        b /= 10;
        i++;
    }
    result.sign = sign;
    result.length = get_length(*result.numbers);
    return result;
}

LongNumber LongNumber::operator - (const LongNumber& x) {
    LongNumber result;
    if (x.sign < 0) { return operator+(x); }
    int a = abs(*numbers);
    int b = abs(*x.numbers);
    int total_length = std::max(length, x.length);
    int i = 0;
    while (i < total_length) {
        *result.numbers += (int)((((a % 10) - (b % 10)) * pow(10, i)) * (sign)); //не видит pow, возможно, так же реализовать вручную 
        a /= 10;
        b /= 10;
        i++;
    }
    result.sign = sign;
    result.length = get_length(*result.numbers);
    return result;

}


LongNumber LongNumber::operator * (const LongNumber& x) {
    LongNumber result;

    int a = *numbers;
    int b = *x.numbers;
    int total_length = std::max(length, x.length);
    int i = 0;
    int k = 1;
    while ((i < total_length) && (k < total_length)) {
        *result.numbers += (((a * (b % (int)pow(10, k))) * pow(10, i)));
        b /= 10;
        i++;
    }
    result.sign = sign == x.sign ? POSITIVE : NEGATIVE;
    result.length = get_length(*result.numbers);
    return result;
}

LongNumber LongNumber::operator / (const LongNumber& x) { //переделать, согласно крайним случаям
    LongNumber result;
    int a = *numbers;
    int b = *x.numbers;
    if (length < x.length) {
        *result.numbers = 0;
        result.sign = POSITIVE;
        result.length = 1;
    }
    else if (abs(a) == abs(b)) {
        *result.numbers = 1;
        result.sign = std::min(sign, x.sign);
        result.length = 1;
    }

    else {
        int total_length = std::max(length, x.length);
        int i = length - x.length;
        int point = a / pow(10, length - x.length) >= b ? pow(10, length - x.length) : pow(10, length - x.length - 1); //+-1?
        *result.numbers += (a / point / b) * pow(10, i);
        //i--;
        while (i != 0) {

            int tmp = a / point - (a / point / b) * b;
            a = (tmp * pow(10, i)) + (a % (int)pow(10, i)); //везде был - 1
            i--;
            int len = get_length(a);
            point = a / pow(10, len - x.length) >= b ? pow(10, len - x.length) : pow(10, len - x.length - 1);
            if (point == 1) {
                *result.numbers += (a / point / b) * pow(10, i - 1);
            }
            else {
                *result.numbers += (a / point / b) * pow(10, i);
            }
            //*result.numbers += (a / point / b) * pow(10, i);
            //break;
        }
        result.sign = sign == x.sign ? POSITIVE : NEGATIVE;
        result.length = get_length(*result.numbers);
    }
    return result;
}


int LongNumber::reverse_digits(int num)
{
    int rev_num = 0;
    while (num > 0) {
        rev_num = rev_num * 10 + num % 10;
        num = num / 10;
    }
    return rev_num;
}


int LongNumber::get_length(int x) {  //распараллелить с get_digits, чтобы сделать private
    return ((bool)x * (int)log10(abs(x)) + 1);
}

bool LongNumber::is_negative() const {
	return sign == NEGATIVE;
}




// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace KLikhosherstova {
    std::ostream& operator << (std::ostream& os, const LongNumber& x) {

        os << *x.numbers;
        return os;
    }
}