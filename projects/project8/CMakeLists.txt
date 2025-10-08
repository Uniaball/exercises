cmake_minimum_required(VERSION 3.10)

project(Project8
    VERSION 2.1.0
    DESCRIPTION "一个简易的C系语言工具"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Project8
    src/main/main.cpp
    src/main/help.cpp
    src/main/compiler.cpp
    src/main/wrapper.cpp
    src/main/cmake.cpp
)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()