cmake_minimum_required(VERSION 3.16)
project(PaintQt)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(SOURCES
    main.cpp
    paintwidget.cpp
)

set(HEADERS
    paintwidget.h
)

qt_add_executable(PaintQt
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(PaintQt PRIVATE Qt6::Widgets)