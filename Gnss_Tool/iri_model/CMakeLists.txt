if(CMAKE_CONFIGURATION_TYPES)
  foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER "${config}" config)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config}
      ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
  endforeach()
endif()

set(IRI_L iri2012)

add_subdirectory(iri_2012)
message("Fortran_BINARY_DIR: ${PROJECT_BINARY_DIR}")
include_directories(${PROJECT_BINARY_DIR}/iri_model/iri_2012/fortran_src)
add_subdirectory(c_adapter)

