cmake_minimum_required(VERSION 4.2)
project(funcionesAB_PilaYCola)

set(CMAKE_CXX_STANDARD 20)

add_executable(funcionesAB_PilaYCola main.cpp
        BibliotecaArbolBinario/FuncionesArbolBinario.cpp
        BibliotecaColas/FuncionesCola.cpp)
