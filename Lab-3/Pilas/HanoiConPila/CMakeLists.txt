cmake_minimum_required(VERSION 4.2)
project(HanoiConPila)

set(CMAKE_CXX_STANDARD 20)

add_executable(HanoiConPila main.cpp
        BibliotecaPilas/funcionesPila.cpp)
