cmake_minimum_required(VERSION 3.20)

set(VCPKG_TARGET_TRIPLET "x64-windows")
set(VCPKG_HOST_TRIPLET "x64-windows")

project(gantt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)
find_package(ArcGISRuntime 100.15.2 REQUIRED COMPONENTS Cpp)

set(mapping_sources
    MainWindow.h
    MainWindow.cpp
)

add_executable(example main.cpp ${mapping_sources})
target_link_libraries(example PRIVATE Qt5::Widgets Qt5::Network ArcGISRuntime::Cpp)

