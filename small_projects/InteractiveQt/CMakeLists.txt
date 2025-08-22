cmake_minimum_required(VERSION 3.16)
project(InteractiveQt)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(SOURCES main.cpp)

qt_add_executable(InteractiveQt
    ${SOURCES}
)

target_link_libraries(InteractiveQt PRIVATE Qt6::Widgets)