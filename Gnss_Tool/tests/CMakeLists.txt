set(GTOOL_TEST gtool_test)

enable_testing()

if (NOT GTEST_INCLUDE_DIR)
   find_package(GTest REQUIRED)
endif()
message("GTest: ${GTEST_INCLUDE_DIR}, lib: ${GTEST_LIBRARY}, main_lib: ${GTEST_MAIN_LIBRARY}")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIR}
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/unit)
