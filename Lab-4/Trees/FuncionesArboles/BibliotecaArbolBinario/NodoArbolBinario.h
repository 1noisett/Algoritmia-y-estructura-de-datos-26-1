//
// Created by Miguel Bazan on 10/06/26.
//

#ifndef FUNCIONESARBOLES_NODOARBOLBINARIO_H
#define FUNCIONESARBOLES_NODOARBOLBINARIO_H
#include "ElementoArbolBinario.h"

struct NodoArbolBinario {
    ElementoArbolBinario elemento;
    NodoArbolBinario *izq;
    NodoArbolBinario *der;
};

#endif //FUNCIONESARBOLES_NODOARBOLBINARIO_H
