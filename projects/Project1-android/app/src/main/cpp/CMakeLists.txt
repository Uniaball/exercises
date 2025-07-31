cmake_minimum_required(VERSION 3.10)
project("project1")

add_library(game SHARED main.cpp)

find_library(log-lib log)

target_link_libraries(game
    android
    ${log-lib}
)