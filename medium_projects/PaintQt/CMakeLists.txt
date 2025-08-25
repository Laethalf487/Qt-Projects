cmake_minimum_required(VERSION 3.16)
project(PaintQt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(SOURCES
    main.cpp
    paintwidget.cpp
)

qt_add_executable(PaintQt
    ${SOURCES}
)

target_link_libraries(PaintQt PRIVATE Qt6::Widgets)