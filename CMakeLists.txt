cmake_minimum_required(VERSION 3.10.0)
project(SnakeGame VERSION 0.1.0 LANGUAGES C)

include_directories(SnakeGame/include)

file(GLOB SOURCES "SnakeGame/src/*.c" "main.c")
add_executable(SnakeGame ${SOURCES})
