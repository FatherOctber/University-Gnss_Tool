#Subproject for GUI app
set(GUI_APP platform_app)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} include)

file(GLOB_RECURSE _GUI_INCLUDES "include/*.h")
file(GLOB_RECURSE _GUI_SOURCES "src/*.cpp")
file(GLOB_RECURSE _GUI_UI "ui/*.ui")
file(GLOB_RECURSE _GUI_RSC "gui_app.qrc")

qt5_wrap_ui(GUI_UI_HEADERS ${_GUI_UI})
qt5_wrap_cpp(GUI_HDR_MOC ${_GUI_INCLUDES})
qt5_add_resources(GUI_RESOURCE ${_GUI_RSC})

add_library(${GUI_APP}_CONFIG ${GUI_HDR_MOC} ${GUI_UI_HEADERS})
target_link_libraries(${GUI_APP}_CONFIG ${QT5_LIBRARIES} ${UTIL_L} ${PLATFORM_CORE_L})

add_executable(${GUI_APP} ${_GUI_SOURCES} ${_GUI_INCLUDES} ${GUI_RESOURCE})
target_link_libraries(${GUI_APP} ${GUI_APP}_CONFIG)

# install gui app
install (TARGETS ${GUI_APP} RUNTIME DESTINATION bin)
