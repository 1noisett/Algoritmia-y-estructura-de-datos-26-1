cmake_minimum_required(VERSION 4.2)
project(diagonal_iterativo)

set(CMAKE_CXX_STANDARD 20)

add_executable(diagonal_iterativo main.cpp
        BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.cpp
        BibliotecaColas/FuncionesCola.cpp
        BibliotecaPilas/funcionesPila.cpp)
