include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR} include)


file(GLOB_RECURSE _IRI_ADAPTER_INCLUDES "include/*.h")
file(GLOB_RECURSE _IRI_ADAPTER_SOURCES "src/*.cpp")

# Create static library
add_library(${IRI_ADAPTER_L} STATIC ${_IRI_ADAPTER_INCLUDES} ${_IRI_ADAPTER_SOURCES})
target_include_directories(${IRI_ADAPTER_L} PUBLIC include)
target_link_libraries(${IRI_ADAPTER_L} ${IRI_L})

install(FILES ${_IRI_ADAPTER_INCLUDES} DESTINATION include/${IRI_ADAPTER_L})
