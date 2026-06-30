//
// Created by Miguel on 5/3/2026.
//

#ifndef PILASFUNCIONES_NODOPILA_H
#define PILASFUNCIONES_NODOPILA_H
#include "ElementoPila.h"
#include "../BibliotecaArbolBinarioBusqueda/NodoArbolBinarioBusqueda.h"

struct NodoPila {
    NodoArbolBinarioBusqueda *elemento;
    NodoPila *siguiente;
};

#endif //PILASFUNCIONES_NODOPILA_H
