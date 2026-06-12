cmake_minimum_required(VERSION 4.2)
project(FuncionesArboles)

set(CMAKE_CXX_STANDARD 20)

add_executable(FuncionesArboles main.cpp
        BibliotecaArbolBinario/ElementoArbolBinario.h
        BibliotecaArbolBinario/NodoArbolBinario.h
        BibliotecaArbolBinario/ArbolBinario.h
        BibliotecaArbolBinario/FuncionesArbolBinario.cpp
        BibliotecaArbolBinario/FuncionesArbolBinario.h)
