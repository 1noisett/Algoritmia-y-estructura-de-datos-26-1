cmake_minimum_required(VERSION 4.2)
project(FuncionesColas)

set(CMAKE_CXX_STANDARD 20)

add_executable(FuncionesColas main.cpp
        BibliotecaColas/FuncionesCola.cpp
        BibliotecaColas/FuncionesCola.h
        BibliotecaColas/ElementoCola.h
        BibliotecaColas/NodoCola.h
        BibliotecaColas/Cola.h)
