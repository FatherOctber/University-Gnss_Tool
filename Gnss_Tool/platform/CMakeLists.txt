set(PLATFORM platform)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include(GenerateExportHeader)
# set(BUILD_SHARED_LIBS TRUE)
# set(US_BUILD_SHARED_LIBS TRUE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/core)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/gui)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/services)

