#include <gtest/gtest.h>

#include "long_number.hpp"

using KLikhosherstova::LongNumber;

TEST(default_constructor, sign) {
	LongNumber x;
	ASSERT_FALSE(x.is_negative());
}

TEST(default_constructor, length) {
	LongNumber x;
	ASSERT_EQ(1, x.get_length());
}

TEST(default_constructor, length) {
	LongNumber x;
	ASSERT_NE(12, x.get_length());
}

TEST(constructor_with_args, sign) {
	LongNumber x("-123");
	ASSERT_TRUE(x.is_negative());
}

TEST(constructor_with_args, sign) {
	LongNumber x("1523");
	ASSERT_FALSE(x.is_negative());
}

TEST(constructor_with_args, length) {
	LongNumber x("-123");
	ASSERT_EQ(3, x.get_length());
}

TEST(copy_constructor, sign) {
	LongNumber x("1523");
	Long Number y(x);
	ASSERT_FALSE(y.is_negative());
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
