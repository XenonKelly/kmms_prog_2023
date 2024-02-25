target_sources(obuchaika_with_test_lib 
	PRIVATE
		main.cpp
		menu_functions.cpp
		menu_items.cpp	
	PUBLIC
		menu.hpp
		menu_functions.hpp
		menu_items.hpp
)

target_include_directories(obuchaika_with_test_lib PUBLIC
	"${PROJECT_SOURCE_DIR}/src"
)




