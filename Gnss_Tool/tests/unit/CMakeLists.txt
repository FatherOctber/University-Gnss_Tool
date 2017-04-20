set(UNIT unit_tests)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} src)

file(GLOB_RECURSE _UNIT_SOURCES "src/*.cpp")
# test resources
file(GLOB_RECURSE _TEST_RES "res/*.ini")

add_executable(${UNIT} ${_UNIT_SOURCES})

# Link test executable against gtest & gtest_main
target_link_libraries(${UNIT} ${UTIL_L} ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})

add_test(test1 ${UNIT})

# install gui app
install (TARGETS ${UNIT} RUNTIME DESTINATION bin)
install(FILES ${_TEST_RES} DESTINATION test_res)
