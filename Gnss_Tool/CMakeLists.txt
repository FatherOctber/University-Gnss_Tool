cmake_minimum_required(VERSION 2.8.11)

project(gtool)

set(PROJECT_VERSION 0.0.1)

#Sends the -std=c++11 flag to the gcc compiler
ADD_DEFINITIONS(-std=c++11)

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
set(QT5_LIBRARIES Qt5::Core Qt5::Widgets Qt5::SerialPort Qt5::Network)

# utils lib for linkage
set(UTIL_L utils)
set(PLATFORM_CORE_L platform_core)

add_subdirectory(${CMAKE_SOURCE_DIR}/utils)
add_subdirectory(${CMAKE_SOURCE_DIR}/gpstation6_agent)
add_subdirectory(${CMAKE_SOURCE_DIR}/platform)
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)

set(LIBRARIES_COMPONENT lib)
set(HEADERS_COMPONENT devel)


