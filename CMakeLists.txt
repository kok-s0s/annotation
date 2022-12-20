cmake_minimum_required(VERSION 3.1.16)
project(annotation VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

add_executable(annotation
    main.cpp
    Annotation.cpp
    Annotation.ui
    Annotation.qrc
    Frame.cpp
    Manager/ArrowManager.cpp
    Unit/Arrow.cpp
)

target_link_libraries(annotation PRIVATE Qt6::Core Qt6::Widgets)
