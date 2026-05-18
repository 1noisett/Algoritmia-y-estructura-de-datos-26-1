//
// Created by Miguel on 5/17/2026.
//

#ifndef FUNCIONESCOLAS_NODOCOLA_H
#define FUNCIONESCOLAS_NODOCOLA_H
#include "ElementoCola.h"

struct NodoCola {
    ElementoCola elemento;
    NodoCola *siguiente;
};

#endif //FUNCIONESCOLAS_NODOCOLA_H
