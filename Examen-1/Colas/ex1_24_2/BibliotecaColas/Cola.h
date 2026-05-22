//
// Created by Miguel on 5/17/2026.
//

#ifndef FUNCIONESCOLAS_COLA_H
#define FUNCIONESCOLAS_COLA_H
#include "NodoCola.h"

struct Cola {
  NodoCola *inicio;
  NodoCola *VIP;
  NodoCola *fin;
  int longitud;
};

#endif //FUNCIONESCOLAS_COLA_H
