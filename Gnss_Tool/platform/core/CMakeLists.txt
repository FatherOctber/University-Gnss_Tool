# Subproject for platform core
set(CORE platform_core)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} include)

file(GLOB_RECURSE _CORE_INCLUDES "include/*.h")
file(GLOB_RECURSE _CORE_SOURCES "src/*.cpp")

add_definitions(-DPLATFORM_CORE_LIBRARY)

# Create shared library
add_library(${CORE} SHARED ${_CORE_SOURCES} ${_CORE_INCLUDES})
target_link_libraries(${CORE} ${QT5_LIBRARIES} CppMicroServices)

generate_export_header(${CORE})

target_include_directories(${CORE} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

# install
install(TARGETS ${CORE} RUNTIME DESTINATION bin COMPONENT libraries
                        LIBRARY DESTINATION lib COMPONENT libraries
                        ARCHIVE DESTINATION lib/static COMPONENT libraries)

install(FILES ${_CORE_INCLUDES} DESTINATION include/${CORE} COMPONENT headers)
