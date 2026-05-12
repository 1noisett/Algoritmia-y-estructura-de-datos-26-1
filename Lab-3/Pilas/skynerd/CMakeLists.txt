cmake_minimum_required(VERSION 4.2)
project(skynerd)

set(CMAKE_CXX_STANDARD 20)

add_executable(skynerd main.cpp
        BibliotecaPilas/funcionesPila.cpp)
