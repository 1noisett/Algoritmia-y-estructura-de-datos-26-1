//
// Created by Miguel on 5/3/2026.
//

#ifndef PILASFUNCIONES_FUNCIONESPILA_H
#define PILASFUNCIONES_FUNCIONESPILA_H
#include "Pila.h"

void construirPila(Pila &pilaTAD);
bool esPilaVacia(Pila &pilaTAD);
int longitudPila(Pila &pilaTAD);
NodoArbolBinarioBusqueda *cima(Pila &pilaTAD);
void apilar(Pila &pilaTAD,NodoArbolBinarioBusqueda *elemento);
NodoArbolBinarioBusqueda *desapilar(Pila &pilaTAD);
void destruirPila(Pila &pilaTAD);
void imprimirPila(Pila &pilaTAD);





#endif //PILASFUNCIONES_FUNCIONESPILA_H
