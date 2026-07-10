//
// Created by Miguel on 5/17/2026.
//

#ifndef FUNCIONESCOLAS_NODOCOLA_H
#define FUNCIONESCOLAS_NODOCOLA_H
#include "ElementoCola.h"
#include "../BibliotecaArbolBinarioBusqueda/NodoArbolBinarioBusqueda.h"

struct NodoCola {
    NodoArbolBinarioBusqueda *nodo;
    NodoCola *siguiente;
};

#endif //FUNCIONESCOLAS_NODOCOLA_H
