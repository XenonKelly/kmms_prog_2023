#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "menu_items.hpp"

TEST(TitleEqual, Subject){
	const KLikhosherstova::MenuItem* actual_title = KLikhosherstova::MATHAN_INT.parent;
  	const KLikhosherstova::MenuItem* expected_title = &KLikhosherstova::STUDY;
  	ASSERT_EQ(actual_title, expected_title)
  		<< "Неверный результат";
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}