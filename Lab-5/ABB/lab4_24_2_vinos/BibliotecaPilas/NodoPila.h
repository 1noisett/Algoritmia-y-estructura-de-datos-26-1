//
// Created by Miguel on 5/3/2026.
//

#ifndef PILASFUNCIONES_NODOPILA_H
#define PILASFUNCIONES_NODOPILA_H
#include "ElementoPila.h"

struct NodoPila {
    ElementoPila elemento;
    NodoPila *siguiente;
};

#endif //PILASFUNCIONES_NODOPILA_H
