//
// Created by Miguel Bazan on 23/06/26.
//

#ifndef FUNCIONESABB_NODOARBOLBINARIOBUSQUEDA_H
#define FUNCIONESABB_NODOARBOLBINARIOBUSQUEDA_H
#include "ElementoArbolBinarioBusqueda.h"

struct NodoArbolBinarioBusqueda {
    ElementoArbolBinarioBusqueda elemento;
    NodoArbolBinarioBusqueda *izq;
    NodoArbolBinarioBusqueda *der;
};

#endif //FUNCIONESABB_NODOARBOLBINARIOBUSQUEDA_H
