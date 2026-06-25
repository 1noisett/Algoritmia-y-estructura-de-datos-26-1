//
// Created by Miguel on 5/17/2026.
//

#ifndef FUNCIONESCOLAS_NODOCOLA_H
#define FUNCIONESCOLAS_NODOCOLA_H
#include "ElementoCola.h"
#include "../BibliotecaArbolBinario/NodoArbolBinario.h"

struct NodoCola {
    NodoArbolBinario *nodo;
    NodoCola *siguiente;
};

#endif //FUNCIONESCOLAS_NODOCOLA_H
