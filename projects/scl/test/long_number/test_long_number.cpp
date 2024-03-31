#include <gtest/gtest.h>

#include "long_number.hpp"

using KLikhosherstova::LongNumber;

TEST(is_negative, sign){
	LongNumber x;
	ASSERT_EQ(0, x.is_negative());
}

TEST(is_negative, sign) {
	LongNumber x;
	ASSERT_FALSE(x.is_negative());
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
