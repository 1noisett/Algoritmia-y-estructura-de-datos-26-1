//
// Created by Miguel Bazan on 10/06/26.
//
#include "FuncionesArbolBinario.h"
#include <iomanip>
#include <iostream>
#include "ArbolBinario.h"
using namespace std;

void construir(ArbolBinario &arbol) {
    arbol.raiz = nullptr;
}

bool esArbolVacio(ArbolBinario &arbol) {
    return arbol.raiz == nullptr;
}

bool esNodoVacio(NodoArbolBinario *nodo) {
    return nodo==nullptr;
}

void plantarArbolBinario(ArbolBinario &arbol, const ArbolBinario &izq, const ElementoArbolBinario &elemento,
                         const ArbolBinario &der) {
    plantarNodoArbolBinario(arbol.raiz,izq.raiz,elemento,der.raiz);
}

// “No te dejo guardar un const NodoArbolBinario * dentro de un NodoArbolBinario *.”
void plantarNodoArbolBinario(NodoArbolBinario *&nodo,NodoArbolBinario *izq,const ElementoArbolBinario &elemento,
                            NodoArbolBinario *der) {
    NodoArbolBinario *nuevo = new NodoArbolBinario;
    nuevo->der = der;
    nuevo->izq = izq;
    nuevo->elemento = elemento;
    nodo = nuevo;
}

void recorrerPreOrder(const ArbolBinario &arbol) {
    recorrerPreOrderRecursivo(arbol.raiz);
}

void recorrerPreOrderRecursivo(NodoArbolBinario *nodo) {
    if (!esNodoVacio(nodo)) {
        imprimirNodo(nodo);
        recorrerPreOrderRecursivo(nodo->izq);
        recorrerPreOrderRecursivo(nodo->der);
    }
}

void recorrerInOrder(const ArbolBinario &arbol) {
    recorrerInOrderRecursivo(arbol.raiz);
}

void recorrerInOrderRecursivo(NodoArbolBinario *nodo) {
    if (!esNodoVacio(nodo)) {
        recorrerInOrderRecursivo(nodo->izq);
        imprimirNodo(nodo);
        recorrerInOrderRecursivo(nodo->der);
    }
}

void recorrerPostOrder(const ArbolBinario &arbol) {
    recorrerPostOrderRecursivo(arbol.raiz);
}

void recorrerPostOrderRecursivo(NodoArbolBinario *nodo) {
    if (!esNodoVacio(nodo)) {
        recorrerPostOrderRecursivo(nodo->izq);
        recorrerPostOrderRecursivo(nodo->der);
        imprimirNodo(nodo);
    }
}

int numeroNodos(const ArbolBinario &arbol) {
    return numeroNodosRecursivo(arbol.raiz);
}

int numeroNodosRecursivo(NodoArbolBinario *nodo) {
    if (esNodoVacio(nodo)) {
        return 0;
    }else {
        return 1 + numeroNodosRecursivo(nodo->izq) + numeroNodosRecursivo(nodo->der);
    }
}

int numeroHojas(const ArbolBinario &arbol) {
    return numeroHojasRecursivo(arbol.raiz);
}

int numeroHojasRecursivo(NodoArbolBinario *nodo) {
    if (esNodoVacio(nodo)) {
        return 0;
    }else if (nodo->izq == nullptr && nodo->der==nullptr) {
        return 1;
    }else {
        return numeroHojasRecursivo(nodo->izq) + numeroHojasRecursivo(nodo->der);
    }
}

int maximo(int num1,int num2) {
    return (num1 >= num2) ? num1 : num2;
}

int altura(const ArbolBinario &arbol) {
    return alturaRecursivo(arbol.raiz);
}

int alturaRecursivo(NodoArbolBinario *nodo) {
    if (esNodoVacio(nodo)) {
        return 0;
    }else if (nodo->izq == nullptr && nodo->der==nullptr) {
        return 0;
    }else {
        return 1 + maximo(alturaRecursivo(nodo->izq),alturaRecursivo(nodo->der));
    }
}

/*
Un árbol binario está equilibrado si para cada nodo
la diferencia de alturas entre sus hijos izquierdo y derecho es como máximo 1.
*/

bool esEquilibrado(const ArbolBinario &arbol) {
    return esEquilibradoRecursivo(arbol.raiz);
}

bool esEquilibradoRecursivo(NodoArbolBinario *nodo) {
    if (esNodoVacio(nodo)) {
        return true;
    }else {
        int alturaIzq = alturaRecursivo(nodo->izq);
        int alturaDer = alturaRecursivo(nodo->der);
        int diferencia = abs(alturaIzq-alturaDer);
        return diferencia<=1 && esEquilibradoRecursivo(nodo->izq) && esEquilibradoRecursivo(nodo->der);
    }
}

void destruirArbolBinario(ArbolBinario &arbol) {
    destruirRecursivo(arbol.raiz);
    arbol.raiz = nullptr;
}

void destruirRecursivo(NodoArbolBinario *nodo) {
    if (!(esNodoVacio(nodo))) {
        destruirRecursivo(nodo->izq);
        destruirRecursivo(nodo->der);
        delete nodo;
    }
}

void imprimirNodo(NodoArbolBinario *raiz) {
    cout<<raiz->elemento.bit<<"-"<<raiz->elemento.valor<<"  ";
}