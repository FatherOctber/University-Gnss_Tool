cmake_minimum_required(VERSION 2.8)
project(IRI_2012 Fortran C)

file(GLOB_RECURSE _IRI_F_SRC "*.for")

add_library(iri2012 SHARED ${_IRI_F_SRC})
target_link_libraries(iri2012)

