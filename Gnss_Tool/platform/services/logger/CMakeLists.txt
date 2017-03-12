# Log service
set(LOGGER log_service)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} include)

# [interface-begin]

add_library(ILogger SHARED ${CMAKE_CURRENT_SOURCE_DIR}/ifce/ILogger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ifce/ILogger.cpp)

target_include_directories(ILogger PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ifce>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

generate_export_header(ILogger)

set_target_properties(ILogger PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN 1
    )
# [interface-end]

# [publisher-begin]
#=========================================================
# A bundle implementing the ILogger interface
#---------------------------------------------------------

set(_LOGGER_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/impl/Logger.cpp
)

# Set up dependencies to resources to track changes
usFunctionGetResourceSource(TARGET Logger OUT _LOGGER_SRC)
# Generate bundle initialization code
usFunctionGenerateBundleInit(TARGET Logger OUT _LOGGER_SRC)

add_library(Logger SHARED ${_LOGGER_SRC})

target_link_libraries(Logger CppMicroServices ILogger ${QT5_LIBRARIES})

set(_logger_bundle logger)

set_target_properties(Logger PROPERTIES
  # This is required for every bundle
  COMPILE_DEFINITIONS US_BUNDLE_NAME=${_logger_bundle}
  # This is for convenience, used by other CMake functions
  US_BUNDLE_NAME ${_logger_bundle}
  )

set_target_properties(Logger PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN 1
    )

# Embed meta-data from a manifest.json file
usFunctionEmbedResources(TARGET Logger
  WORKING_DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/impl
  FILES
    manifest.json
  )

# [publisher-end]
install(TARGETS ILogger RUNTIME DESTINATION bin COMPONENT libraries
                                                      LIBRARY DESTINATION lib COMPONENT libraries
                                                      ARCHIVE DESTINATION lib/static COMPONENT libraries)

install(TARGETS Logger RUNTIME DESTINATION bin COMPONENT libraries
                             LIBRARY DESTINATION lib COMPONENT libraries
                             ARCHIVE DESTINATION lib/static COMPONENT libraries)




