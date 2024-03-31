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
		LongNumber(int value);
		LongNumber(const char* const str);
		LongNumber(const LongNumber& x);
		LongNumber(LongNumber&& x);

		~LongNumber();

		LongNumber& operator = (const char* const str);
		LongNumber& operator = (int value);
		LongNumber& operator = (const LongNumber& x);
		LongNumber& operator = (LongNumber&& x);

		bool operator==(const LongNumber& x) const;
		bool operator!=(const LongNumber& x) const;
		bool operator>(const LongNumber& x) const;
		bool operator<(const LongNumber& x) const;

		LongNumber operator+(const LongNumber& x) const;
		LongNumber operator-(const LongNumber& x) const;
		LongNumber operator*(const LongNumber& x) const;
		LongNumber operator/(const LongNumber& x) const;
		LongNumber operator%(const LongNumber& x) const;

		int get_length(int x) const;
		int get_length(const char* const str) const;
		bool is_negative() const;
		int reverse_digits(int x) const;
		int to_int(const LongNumber& x) const;
		
		friend std::ostream& operator << (std::ostream& os, const LongNumber& x);

	};

}