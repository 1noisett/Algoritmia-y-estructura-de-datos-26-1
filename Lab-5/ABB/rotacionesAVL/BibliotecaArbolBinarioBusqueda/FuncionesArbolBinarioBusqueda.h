//
// Created by Miguel Bazan on 23/06/26.
//

#ifndef FUNCIONESABB_FUNCIONESARBOLBINARIOBUSQUEDA_H
#define FUNCIONESABB_FUNCIONESARBOLBINARIOBUSQUEDA_H
#include "ArbolBinarioBusqueda.h"

// funciones del ejercicio AVL
int ALTURA(NodoArbolBinarioBusqueda *nodo);
int FACTOR_BALANCE(NodoArbolBinarioBusqueda *nodo);
NodoArbolBinarioBusqueda *rotacionDerecha(NodoArbolBinarioBusqueda *y);
NodoArbolBinarioBusqueda *rotacionIzquierda(NodoArbolBinarioBusqueda *x);
NodoArbolBinarioBusqueda *insertarAVLRecursivo(NodoArbolBinarioBusqueda *nodo,int clave);
void insertarAVL(ArbolBinarioBusqueda &arbol,int clave);

void construir(ArbolBinarioBusqueda &arbol);
bool esArbolVacio(const ArbolBinarioBusqueda &arbol);
bool esNodoVacio(NodoArbolBinarioBusqueda *nodo);

void plantarArbolBinario(ArbolBinarioBusqueda &arbol,const ArbolBinarioBusqueda &izq,
                        const ElementoArbolBinarioBusqueda &elemento,const ArbolBinarioBusqueda &der);
void plantarNodoArbolBinario(NodoArbolBinarioBusqueda *&nodo,NodoArbolBinarioBusqueda *izq,
                                    const ElementoArbolBinarioBusqueda &elemento,NodoArbolBinarioBusqueda *der);

void recorrerPreOrder(const ArbolBinarioBusqueda &arbol);
void recorrerPreOrderRecursivo(NodoArbolBinarioBusqueda *nodo);
void recorrerInOrder(const ArbolBinarioBusqueda &arbol);
void recorrerInOrderRecursivo(NodoArbolBinarioBusqueda *nodo);
void recorrerPostOrder(const ArbolBinarioBusqueda &arbol);
void recorrerPostOrderRecursivo(NodoArbolBinarioBusqueda *nodo);
int numeroHojas(const ArbolBinarioBusqueda &arbol);
int numeroHojasRecursivo(NodoArbolBinarioBusqueda *nodo);
int numeroNodos(const ArbolBinarioBusqueda &arbol);
int numeroNodosRecursivo(NodoArbolBinarioBusqueda *nodo);
int maximo(int num1,int num2);
int altura(const ArbolBinarioBusqueda &arbol);
int alturaRecursivo(NodoArbolBinarioBusqueda *nodo);
bool esEquilibrado(const ArbolBinarioBusqueda &arbol);
bool esEquilibradoRecursivo(NodoArbolBinarioBusqueda *nodo);
void destruirArbolBinario(ArbolBinarioBusqueda &arbol);
void destruirRecursivo(NodoArbolBinarioBusqueda *nodo);
void imprimirNodo(NodoArbolBinarioBusqueda *nodo);

void insertar(ArbolBinarioBusqueda &arbol,const ElementoArbolBinarioBusqueda &elemento);
void insertarRecursivo(NodoArbolBinarioBusqueda *&raiz,const ElementoArbolBinarioBusqueda &elemento);
int comparaElementos(int elemA,int elemB);
bool buscarRecursivo(NodoArbolBinarioBusqueda *nodo,const ElementoArbolBinarioBusqueda &elemento);
bool buscar(const ArbolBinarioBusqueda &arbol,const ElementoArbolBinarioBusqueda &elemento);
void eliminar(ArbolBinarioBusqueda &arbol,const ElementoArbolBinarioBusqueda &elemento);
NodoArbolBinarioBusqueda *eliminarRecursivo(NodoArbolBinarioBusqueda *nodo,const ElementoArbolBinarioBusqueda &elemento);
NodoArbolBinarioBusqueda *minimoArbol(NodoArbolBinarioBusqueda *nodo);


#endif //FUNCIONESABB_FUNCIONESARBOLBINARIOBUSQUEDA_H
