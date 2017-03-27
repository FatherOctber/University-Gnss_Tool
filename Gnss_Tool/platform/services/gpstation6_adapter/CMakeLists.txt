#Subproject for services interfaces and implementations
set(GP6ADAPTER gp6adapter_service)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} include)

# [interface-begin]

add_library(IGP6Adapter SHARED ${CMAKE_CURRENT_SOURCE_DIR}/ifce/IGP6Adapter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ifce/IGP6Adapter.cpp)

target_include_directories(IGP6Adapter PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ifce>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

generate_export_header(IGP6Adapter)

set_target_properties(IGP6Adapter PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN 1
    )
# [interface-end]

# [publisher-begin]
#=========================================================
# A bundle implementing the IGP6Adapter interface
#---------------------------------------------------------

set(_GP6ADAPTER_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/GP6Adapter.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/GP6Client.h
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/GP6Client.cpp
)

# Set up dependencies to resources to track changes
usFunctionGetResourceSource(TARGET GP6Adapter OUT _GP6ADAPTER_SRC)
# Generate bundle initialization code
usFunctionGenerateBundleInit(TARGET GP6Adapter OUT _GP6ADAPTER_SRC)

add_library(GP6Adapter SHARED ${_GP6ADAPTER_SRC})

target_link_libraries(GP6Adapter CppMicroServices IGP6Adapter ${SERVICE_PARENT} ${QT5_LIBRARIES})

set(_gp6adapter_bundle gp6adapter)

set_target_properties(GP6Adapter PROPERTIES
  # This is required for every bundle
  COMPILE_DEFINITIONS US_BUNDLE_NAME=${_gp6adapter_bundle}
  # This is for convenience, used by other CMake functions
  US_BUNDLE_NAME ${_gp6adapter_bundle}
  )

set_target_properties(GP6Adapter PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN 1
    )

# Embed meta-data from a manifest.json file
usFunctionEmbedResources(TARGET GP6Adapter
  WORKING_DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/impl
  FILES
    manifest.json
  )

# [publisher-end]
install(TARGETS IGP6Adapter RUNTIME DESTINATION bin COMPONENT libraries
                                                      LIBRARY DESTINATION lib COMPONENT libraries
                                                      ARCHIVE DESTINATION lib/static COMPONENT libraries)

install(TARGETS GP6Adapter RUNTIME DESTINATION bin COMPONENT libraries
                             LIBRARY DESTINATION lib COMPONENT libraries
                             ARCHIVE DESTINATION lib/static COMPONENT libraries)



