cmake_minimum_required(VERSION 4.2)
project(PilasFunciones)

set(CMAKE_CXX_STANDARD 20)

add_executable(PilasFunciones main.cpp
        BibliotecaPilas/funcionesPila.cpp
        BibliotecaPilas/funcionesPila.h
        BibliotecaPilas/ElementoPila.h
        BibliotecaPilas/NodoPila.h
        BibliotecaPilas/Pila.h)
