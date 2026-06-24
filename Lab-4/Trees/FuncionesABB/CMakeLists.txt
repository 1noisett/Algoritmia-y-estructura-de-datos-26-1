cmake_minimum_required(VERSION 4.2)
project(FuncionesABB)

set(CMAKE_CXX_STANDARD 20)

add_executable(FuncionesABB main.cpp
        BibliotecaArbolBinarioBusqueda/NodoArbolBinarioBusqueda.h
        BibliotecaArbolBinarioBusqueda/ElementoArbolBinarioBusqueda.h
        BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h
        BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.cpp
        BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h)
