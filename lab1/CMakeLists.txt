cmake_minimum_required(VERSION 4.1)

project(lab1 CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab1 main.cpp)

set_target_properties(lab1 PROPERTIES 
    CXX_SCAN_FOR_MODULES ON
    CXX_MODULE_STD ON
)

target_sources(lab1 
    PRIVATE 
        FILE_SET modules TYPE CXX_MODULES FILES matrix.ixx
)
