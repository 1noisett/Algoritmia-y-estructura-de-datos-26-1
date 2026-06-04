cmake_minimum_required(VERSION 4.2)
project(ejercicios)

set(CMAKE_CXX_STANDARD 20)

add_executable(ejercicios main.cpp
        FuncionesDivideConquer.cpp
        FuncionesDivideConquer.h
        MaxSubArray.cpp
        MaxSubArray.h
        ContarCeros.cpp
        ContarCeros.h
        ContarInversiones.cpp
        ContarInversiones.h)
