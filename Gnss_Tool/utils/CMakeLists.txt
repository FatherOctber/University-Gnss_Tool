#Subproject for UTILS lib
set(UTILS_LIB utils)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR} include)


file(GLOB_RECURSE _UTILS_INCLUDES "include/*.h")
file(GLOB_RECURSE _UTILS_SOURCES "src/*.cpp")

# Create static library
add_library(${UTILS_LIB} STATIC ${_UTILS_SOURCES} ${_UTILS_INCLUDES})

target_include_directories(${UTILS_LIB} PUBLIC include)
target_link_libraries(${UTILS_LIB} ${QT5_LIBRARIES})

install(TARGETS ${UTILS_LIB} ARCHIVE DESTINATION lib/static)
install(FILES ${_UTILS_INCLUDES} DESTINATION include/${UTILS_LIB})
