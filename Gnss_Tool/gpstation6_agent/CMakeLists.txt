#Subproject for GPStation-6 connection agent
set(GPSTATION6_AGENT gpstation6-agent)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} include)

file(GLOB_RECURSE _GPA_INCLUDES "include/*.h")
file(GLOB_RECURSE _GPA_SOURCES "src/*.cpp")
file(GLOB_RECURSE _GPA_UI "ui/*.ui")
file(GLOB_RECURSE _GPA_RSC "terminal.qrc")

qt5_wrap_ui(GPA_UI_HEADERS ${_GPA_UI})
qt5_add_resources(GPA_RESOURCE ${_GPA_RSC})
qt5_wrap_cpp(GPA_HDR_MOC ${_GPA_INCLUDES})

add_library(${GPSTATION6_AGENT}_CONFIG ${GPA_HDR_MOC} ${GPA_UI_HEADERS})
target_link_libraries(${GPSTATION6_AGENT}_CONFIG ${QT5_LIBRARIES} ${UTIL_L})

add_executable(${GPSTATION6_AGENT} ${_GPA_SOURCES} ${_GPA_INCLUDES} ${GPA_RESOURCE})
target_link_libraries(${GPSTATION6_AGENT} ${GPSTATION6_AGENT}_CONFIG)

