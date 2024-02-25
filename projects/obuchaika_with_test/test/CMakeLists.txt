set(SOURCES
	obuchaika_test.cpp
)

add_executable(obuchaika_test ${SOURCES})
target_link_libraries(obuchaika_test
	gtest_main
	gmock_main
	obuchaika_with_test_lib
)

add_test(obuchaika_test obuchaika_test)