cmake_minimum_required(VERSION 3.29)
project(yutnori)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(Qt6_DIR "/home/junjinyong/Qt/6.8.2/gcc_64/lib/cmake/Qt6")

find_package(Qt6 REQUIRED COMPONENTS
        Core
        Gui
        UiPlugin
        Widgets
        SvgWidgets
        Svg)

add_executable(yutnori main.cpp images.qrc)

target_include_directories(yutnori PRIVATE include)

target_sources(yutnori
        PRIVATE
        src/window.cpp
        src/board.cpp
        src/team.cpp
        src/piece.cpp
        src/dialog.cpp
        src/sign.cpp
        include/window.h
        include/board.h
        include/team.h
        include/piece.h
        include/dialog.h
        include/sign.h
)

target_link_libraries(yutnori
        Qt::Core
        Qt::Widgets
        Qt::SvgWidgets
        Qt::Svg
)
