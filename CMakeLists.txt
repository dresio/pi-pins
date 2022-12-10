cmake_minimum_required(VERSION 3.16)
project(gpio_control)

set(CMAKE_CXX_STANDARD 11)

add_executable(gpio_control src/PinControl.cpp)