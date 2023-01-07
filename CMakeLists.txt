cmake_minimum_required(VERSION 3.5)

project(checkers LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
        src/authorizationdialog.cpp
        src/authorizationdialog.h
        src/authorizationdialog.ui
        src/cell.cpp
        src/cell.h
        src/checker.cpp
        src/checker.h
        src/field.cpp
        src/field.h
        src/fieldwidget.cpp
        src/fieldwidget.h
        src/game.cpp
        src/game.h
        src/optionwidget.cpp
        src/optionwidget.h
        src/selectionwidget.cpp
        src/selectionwidget.h
        src/settingsdialog.cpp
        src/settingsdialog.h
        src/settingsdialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(checkers
        ${PROJECT_SOURCES} resources/resources.qrc
    )
else()
    if(ANDROID)
        add_library(checkers SHARED
            ${PROJECT_SOURCES} resources/resources.qrc
        )
    else()
        add_executable(checkers
            ${PROJECT_SOURCES} resources/resources.qrc
        )
    endif()
endif()

target_link_libraries(checkers PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
