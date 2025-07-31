cmake_minimum_required(VERSION 3.10)
project("project1_android")

add_library(project1_android SHARED main.cpp)

find_library(log-lib log)

target_link_libraries(project1_android
    android
    ${log-lib}
)