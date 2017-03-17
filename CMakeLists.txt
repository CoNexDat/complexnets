cmake_minimum_required (VERSION 3.6)
project (complexnets)

set_property(GLOBAL PROPERTY CXX_STANDARD 14)

set(CMAKE_C_COMPILER, gcc-6)
set(CMAKE_CXX_COMPILER, g++-6)

set(CMAKE_PREFIX_PATH /usr/local/opt/qt5)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

add_definitions(-DNO_BITWISE_ENUMS)

include_directories(.)

# Find the QtWidgets library
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_subdirectory(ComplexNets)
add_subdirectory(ComplexNetsCmd)
add_subdirectory(ComplexNetsGui)
