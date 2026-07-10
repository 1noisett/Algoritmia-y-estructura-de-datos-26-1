cmake_minimum_required(VERSION 4.2)
project(abb_iterativo_practicar)

set(CMAKE_CXX_STANDARD 20)

add_executable(abb_iterativo_practicar main.cpp
        BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.cpp
        BibliotecaColas/FuncionesCola.cpp
        BibliotecaPilas/funcionesPila.cpp)
