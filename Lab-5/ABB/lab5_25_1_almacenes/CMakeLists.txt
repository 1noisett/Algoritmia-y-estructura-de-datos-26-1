cmake_minimum_required(VERSION 4.2)
project(lab5_25_1_almacenes)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab5_25_1_almacenes main.cpp
        BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.cpp
        BibliotecaColas/FuncionesCola.cpp)
