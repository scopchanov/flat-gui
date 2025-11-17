find_package(Qt6 REQUIRED COMPONENTS Widgets Test)

enable_testing()

file(GLOB TEST_SOURCES tst_*.cpp)

foreach(test_src ${TEST_SOURCES})
	get_filename_component(base_name ${test_src} NAME_WE)
	string(REPLACE "tst_" "" stripped_name ${base_name})
	set(test_name "${stripped_name}Test")
	add_executable(${test_name} ${test_src})
	target_link_libraries(${test_name} PRIVATE Qt6::Widgets Qt6::Test ${PROJECT_NAME})
	add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
