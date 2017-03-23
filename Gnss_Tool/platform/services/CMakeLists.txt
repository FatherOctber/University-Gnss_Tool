#Subproject for services interfaces and implementations
set(SERVICES platform_services)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR} src)

file(GLOB_RECURSE _SERVICE_SOURCES "src/*.cpp")
file(GLOB_RECURSE _SERVICE_HEADERS "src/*.h")

# Create static library
add_library(${SERVICES} ${_SERVICE_HEADERS} ${_SERVICE_SOURCES})

target_include_directories(${SERVICES} PUBLIC include)
target_link_libraries(${SERVICES} ${QT5_LIBRARIES})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/db_adapter)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/gpstation6_adapter)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/iono_diagnostic)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/logger)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tec_correction)
