# Core transport layer
set(TRANSPORT transport_consumer)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} include)

file(GLOB_RECURSE _TRANSPORT_HEADERS "impl/*.h")
file(GLOB_RECURSE _TRANSPORT_SOURCES "impl/*.cpp")

usFunctionGetResourceSource(TARGET transport_consumer OUT _TRANSPORT_SOURCES)
usFunctionGenerateBundleInit(TARGET transport_consumer OUT _TRANSPORT_SOURCES)

add_library(${TRANSPORT} SHARED ${_TRANSPORT_SOURCES} ${_TRANSPORT_HEADERS})

# List of available platform services
set(PLATFORM_SERVICES ILogger IGP6Adapter)

target_link_libraries(${TRANSPORT} ${QT5_LIBRARIES} ${UTIL_L} CppMicroServices ${PLATFORM_SERVICES})

set(_transport_bundle transport_consumer)

set_target_properties(transport_consumer PROPERTIES
  COMPILE_DEFINITIONS US_BUNDLE_NAME=${_transport_bundle}
  US_BUNDLE_NAME ${_transport_bundle}
  )

set_target_properties(transport_consumer PROPERTIES
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN 1
  )

usFunctionEmbedResources(TARGET transport_consumer
  WORKING_DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/res
  FILES
    manifest.json
  )

install(TARGETS ${TRANSPORT} RUNTIME DESTINATION bin COMPONENT libraries
                             LIBRARY DESTINATION lib COMPONENT libraries
                             ARCHIVE DESTINATION lib/static COMPONENT libraries)


