cmake_minimum_required(VERSION 3.5)

project(opengl_cmake VERSION 0.1 LANGUAGES CXX C)

add_definitions(-DSOME_IMPORTANT_DEFINITION)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS OpenGL)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

add_subdirectory(third_party/QtGifImage)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.hpp
        mainwindow.ui

        myopenglwidget.hpp
        myopenglwidget.cpp

        ../common/s21_parser.cpp
        ../common/s21_parser.hpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(opengl_cmake
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET opengl_cmake APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(opengl_cmake SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(opengl_cmake
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(opengl_cmake PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(opengl_cmake PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(opengl_cmake PRIVATE Qt6::OpenGL)
target_link_libraries(opengl_cmake PRIVATE Qt6::Gui)
target_link_libraries(opengl_cmake PRIVATE Qt6::Core)
target_link_libraries(opengl_cmake PRIVATE QtGifImage::QtGifImage)

target_include_directories(opengl_cmake PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(opengl_cmake PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(opengl_cmake)
endif()
