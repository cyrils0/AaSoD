cmake_minimum_required(VERSION 4.1)

project(lab2 CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab2 main.cpp)

set_target_properties(lab2 PROPERTIES 
    CXX_SCAN_FOR_MODULES ON
    CXX_MODULE_STD ON
)

