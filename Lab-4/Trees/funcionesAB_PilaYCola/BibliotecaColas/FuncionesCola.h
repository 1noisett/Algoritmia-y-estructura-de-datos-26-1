//
// Created by Miguel on 5/17/2026.
//

#ifndef FUNCIONESCOLAS_FUNCIONESCOLA_H
#define FUNCIONESCOLAS_FUNCIONESCOLA_H
#include "Cola.h"



void construirCola(Cola &colaTAD) ;
bool esColaVacia(const Cola &colaTAD);
int longitudCola(const Cola &colaTAD);
void encolar(Cola &colaTAD, NodoArbolBinario *elemento);
NodoArbolBinario *desencolar(Cola &colaTAD);
void imprimir(const Cola & colaTAD);
void destruir(struct Cola & colaTAD);




#endif //FUNCIONESCOLAS_FUNCIONESCOLA_H
