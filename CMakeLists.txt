cmake_minimum_required(VERSION 3.16)

project(parkinson_app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON) # Handles signals and slots (MOC)
set(CMAKE_AUTOUIC ON) # Handles .ui files (UIC)
set(CMAKE_AUTORCC ON) # Handles resources (RCC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Network)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    src/main.cpp
    src/mainwindow.cpp
    src/filedownloader.cpp
    include/filedownloader.h
    include/mainwindow.h
    src/mainwindow.ui
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
