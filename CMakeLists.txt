cmake_minimum_required(VERSION 3.22)
project(photounloader LANGUAGES CXX)

include(FetchContent)
include(CTest)

FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.3.2
)

FetchContent_MakeAvailable(catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

include_directories(${catch2_SOURCE_DIR}/src)
add_subdirectory(test)
add_subdirectory(src)

add_executable(sample
    getfiles.cpp
)

set_property(TARGET sample PROPERTY CXX_STANDARD 20)