cmake_minimum_required(VERSION 3.16)
project(HelloQt)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(SOURCES main.cpp)

qt_add_executable(HelloQt
    ${SOURCES}
)

# Syntaxe correcte pour Qt6 + CMake moderne
target_link_libraries(HelloQt PRIVATE Qt6::Widgets)
