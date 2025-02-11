cmake_minimum_required(VERSION 3.30)
project(yutnori)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


if(UNIX)
    set(Qt6_DIR "~/Qt/6.8.2/gcc_64/lib/cmake/Qt6")
else()
    set(Qt6_DIR "C:/Qt/6.8.2/mingw_64/lib/cmake/Qt6")
endif()

find_package(Qt6 COMPONENTS REQUIRED Core Gui UiPlugin Widgets SvgWidgets Svg)

add_executable(yutnori main.cpp images.qrc)

target_include_directories(yutnori PRIVATE include)

target_sources(yutnori
        PRIVATE
        include/game.hpp
        include/board.hpp
        include/dialog.hpp
        include/sign.hpp
        include/manager.hpp
)

target_link_libraries(yutnori Qt6::Core Qt6::Widgets Qt6::SvgWidgets Qt6::Svg)
