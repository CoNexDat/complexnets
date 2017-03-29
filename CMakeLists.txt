cmake_minimum_required (VERSION 3.6)
project (complexnets VERSION 1.0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(QtCommon)

fix_project_version()

set(COMPANY "Instituto Tecnológico de Buenos Aires")
set(COPYRIGHT "Instituto Tecnológico de Buenos Aires")
set(IDENTIFIER "ar.edu.itba.ComplexNets")

set_property(GLOBAL PROPERTY CXX_STANDARD 14)

set(CMAKE_C_COMPILER gcc-6)
set(CMAKE_CXX_COMPILER g++-6)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

include_directories(.)

add_compile_options(-Wall -Wextra)
add_project_meta(META_FILES_TO_INCLUDE)

add_definitions(-DNO_BITWISE_ENUMS)

add_subdirectory(ComplexNets)
add_subdirectory(ComplexNetsCmd)
add_subdirectory(ComplexNetsGui)
