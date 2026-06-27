//
// Created by Miguel Bazan on 10/06/26.
//

#ifndef FUNCIONESARBOLES_FUNCIONESARBOLBINARIO_H
#define FUNCIONESARBOLES_FUNCIONESARBOLBINARIO_H
#include "ArbolBinario.h"


void construir(ArbolBinario &arbol);
bool esArbolVacio(ArbolBinario &arbol);
bool esNodoVacio(NodoArbolBinario *nodo);

void plantarArbolBinario(ArbolBinario &arbol, const ArbolBinario &izq, const ElementoArbolBinario &elemento,
                         const ArbolBinario &der);
void plantarNodoArbolBinario(NodoArbolBinario *&nodo,NodoArbolBinario *izq,const ElementoArbolBinario &elemento,
                            NodoArbolBinario *der);

void recorrerPreOrder(const ArbolBinario &arbol);
void recorrerPreOrderRecursivo(NodoArbolBinario *nodo);
void recorrerInOrder(const ArbolBinario &arbol);
void recorrerInOrderRecursivo(NodoArbolBinario *nodo);
void recorrerPostOrder(const ArbolBinario &arbol);
void recorrerPostOrderRecursivo(NodoArbolBinario *nodo);

int numeroNodos(const ArbolBinario &arbol);
int numeroNodosRecursivo(NodoArbolBinario *nodo);
int numeroHojas(const ArbolBinario &arbol);
int numeroHojasRecursivo(NodoArbolBinario *nodo);

int maximo(int num1,int num2);
int altura(const ArbolBinario &arbol);
int alturaRecursivo(NodoArbolBinario *nodo);
bool esEquilibrado(const ArbolBinario &arbol);
bool esEquilibradoRecursivo(NodoArbolBinario *nodo);

void destruirArbolBinario(ArbolBinario &arbol);
void destruirRecursivo(NodoArbolBinario *nodo);

void recorrerPorNiveles(ArbolBinario &arbol);
void recorrerPorNivelCambioLinea(ArbolBinario &arbol);

void imprimirNodo(NodoArbolBinario *raiz);

#endif //FUNCIONESARBOLES_FUNCIONESARBOLBINARIO_H
