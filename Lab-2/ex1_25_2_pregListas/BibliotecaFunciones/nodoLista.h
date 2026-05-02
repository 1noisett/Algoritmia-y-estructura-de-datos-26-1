//
// Created by Miguel Bazan on 21/04/26.
//

#ifndef LISTASFUNCIONES_NODOLISTA_H
#define LISTASFUNCIONES_NODOLISTA_H

#include "elementoLista.h"
struct NodoLista {
    ElementoLista elemento;
    NodoLista *siguiente;
};
#endif //LISTASFUNCIONES_NODOLISTA_H
