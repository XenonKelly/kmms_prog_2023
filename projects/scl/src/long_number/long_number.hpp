#pragma once


#include <iostream>

namespace KLikhosherstova {
	class LongNumber {
		static const char END = '\0';
		static const char ZERO = '0';
		static const char MINUS = '-';
		static const int NEGATIVE = -1;
		static const int POSITIVE = 1;

		int* numbers;
		int length;
		int sign;

	public:
		LongNumber();
		LongNumber(const char* const str);
		LongNumber(const LongNumber& x);
		LongNumber(LongNumber&& x);

		~LongNumber();

		LongNumber& operator = (const char* const str);
		LongNumber& operator = (const LongNumber& x);
		LongNumber& operator = (LongNumber&& x);

		bool operator==(const LongNumber& x);
		bool operator!=(const LongNumber& x);
		bool operator>(const LongNumber& x);
		bool operator<(const LongNumber& x);

		LongNumber operator+(const LongNumber& x);
		LongNumber operator-(const LongNumber& x);
		LongNumber operator*(const LongNumber& x);
		LongNumber operator/(const LongNumber& x);
		LongNumber operator%(const LongNumber& x);
		

		

		int get_digits_number() const;
		bool is_negative() const;
		int get_length(int x);
		int reverse_digits(int x);

		friend std::ostream& operator << (std::ostream& os, const LongNumber& x);

	};

}