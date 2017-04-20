#Subproject for services interfaces and implementations
set(SERVICE_PARENT service_parent)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR} src)

file(GLOB_RECURSE _SERVICE_SOURCES "src/*.cpp")
file(GLOB_RECURSE _SERVICE_HEADERS "src/*.h")

# Create static library
add_library(${SERVICE_PARENT} ${_SERVICE_HEADERS} ${_SERVICE_SOURCES})

target_include_directories(${SERVICE_PARENT} PUBLIC include)
target_link_libraries(${SERVICE_PARENT} ${QT5_LIBRARIES})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/db_adapter)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/gpstation6_adapter)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/iono_diagnostic)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/logger)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tec_correction)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/transport_dispatcher)
