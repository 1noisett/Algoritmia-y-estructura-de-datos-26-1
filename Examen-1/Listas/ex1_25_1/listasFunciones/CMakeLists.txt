cmake_minimum_required(VERSION 4.2)
project(listasFunciones)

set(CMAKE_CXX_STANDARD 20)

add_executable(listasFunciones main.cpp
        listaFunciones.cpp
        listaFunciones.h
        elementoLista.h
        nodoLista.h
        lista.h)
