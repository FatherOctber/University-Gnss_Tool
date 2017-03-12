#Subproject for services interfaces and implementations
set(SERVICES platform_services)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/db_adapter)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/gpstation6_adapter)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/iono_diagnostic)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/logger)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tec_correction)
