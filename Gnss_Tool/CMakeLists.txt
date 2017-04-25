cmake_minimum_required(VERSION 3.1)

project(gtool)

set(PROJECT_VERSION 0.0.1)

#Sends the -std=c++11 flag to the gcc compiler
ADD_DEFINITIONS(-std=c++11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# find package
find_package(Qt5Widgets REQUIRED)
find_package(Qt5SerialPort REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(CppMicroServices REQUIRED)
find_package(Threads REQUIRED)
set(QT5_LIBRARIES Qt5::Core Qt5::Widgets Qt5::SerialPort Qt5::Network)

# internal libs
set(UTIL_L utils)
set(PLATFORM_CORE_L platform_core)
set(IRI_ADAPTER_L iri_adapter)

add_subdirectory(${CMAKE_SOURCE_DIR}/iri_model)
add_subdirectory(${CMAKE_SOURCE_DIR}/utils)
add_subdirectory(${CMAKE_SOURCE_DIR}/gpstation6_agent)
add_subdirectory(${CMAKE_SOURCE_DIR}/platform)
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)

set(LIBRARIES_COMPONENT lib)
set(HEADERS_COMPONENT devel)


