//
// Created by Miguel Bazan on 23/06/26.
//
#include <iomanip>
#include <iostream>
#include "FuncionesArbolBinarioBusqueda.h"
using namespace std;

void insertar(ArbolBinarioBusqueda &arbol,const ElementoArbolBinarioBusqueda &elemento) {
    insertarRecursivo(arbol.raiz,elemento);
}

void insertarRecursivo(NodoArbolBinarioBusqueda *&raiz,const ElementoArbolBinarioBusqueda &elemento) {
    if (esNodoVacio(raiz)) {
        plantarNodoArbolBinario(raiz,nullptr,elemento,nullptr);
    } else {
        int cmp = comparaElementos(raiz->elemento.codAlmacen,elemento.codAlmacen);
        if (cmp==1) {            // raiz mayor: insertar a la izquierda
            insertarRecursivo(raiz->izq,elemento);
        } else if (cmp==-1) {    // raiz menor: insertar a la derecha
            insertarRecursivo(raiz->der,elemento);
        } else {
            // valores iguales: ya existe, no se inserta
            cout<<"El elemento: "<<elemento.codAlmacen<<" ya se encuentra en el arbol"<<endl;
        }
    }
}

int comparaElementos(int elemA,int elemB) {
    if (elemA==elemB) {
        return 0;
    } else if (elemA > elemB) {
        return 1;
    } else {
        return -1;
    }
}

bool buscar(const ArbolBinarioBusqueda &arbol,const ElementoArbolBinarioBusqueda &elemento) {
    return buscarRecursivo(arbol.raiz,elemento);
}

bool buscarRecursivo(NodoArbolBinarioBusqueda *nodo,const ElementoArbolBinarioBusqueda &elemento) {
    if (esNodoVacio(nodo)) {
        return false;
    } else {
        int cmp = comparaElementos(nodo->elemento.codAlmacen,elemento.codAlmacen);
        if (cmp==0) {
            return true;
        } else if (cmp==1) {
            return buscarRecursivo(nodo->izq,elemento);
        } else {
            return buscarRecursivo(nodo->der,elemento);
        }
    }
}

void eliminar(ArbolBinarioBusqueda &arbol,const ElementoArbolBinarioBusqueda &elemento) {
    arbol.raiz = eliminarRecursivo(arbol.raiz,elemento);
}

NodoArbolBinarioBusqueda *eliminarRecursivo(NodoArbolBinarioBusqueda *nodo,const ElementoArbolBinarioBusqueda &elemento) {
    if (esNodoVacio(nodo)) {
        return nodo;
    }
    int cmp = comparaElementos(nodo->elemento.codAlmacen,elemento.codAlmacen);
    if (cmp==1) {            // nodo mayor: el elemento esta a la izquierda
        nodo->izq = eliminarRecursivo(nodo->izq,elemento);
    }else if (cmp==-1) {     // nodo menor: el elemento esta a la derecha
        nodo->der = eliminarRecursivo(nodo->der,elemento);
    }else if (esNodoVacio(nodo->izq)) {    // encontrado, 0 o 1 hijo (derecha)
        NodoArbolBinarioBusqueda *hijo = nodo->der;
        delete nodo;
        return hijo;
    }else if (esNodoVacio(nodo->der)){
        NodoArbolBinarioBusqueda *hijo = nodo->izq;
        delete nodo;
        return hijo;
    }else {                                // encontrado, 2 hijos
        NodoArbolBinarioBusqueda *minNodo = minimoArbol(nodo->der);
        nodo->elemento = minNodo->elemento;
        nodo->der = eliminarRecursivo(nodo->der,minNodo->elemento);
    }
    return nodo; // aplica para cmp 1, -1 y al caso de 2 hijos, donde el nodo no cambia de identidad
                 // sigue siendo la misma posición en el árbol
}

NodoArbolBinarioBusqueda *minimoArbol(NodoArbolBinarioBusqueda *nodo) {
    if (esNodoVacio(nodo)) {
        return nodo;
    }else if (esNodoVacio(nodo->izq)){
        return nodo;
    }else {
        return minimoArbol(nodo->izq);
    }
}

void construir(ArbolBinarioBusqueda &arbol) {
    arbol.raiz = nullptr;
}

bool esArbolVacio(const ArbolBinarioBusqueda &arbol) {
    return arbol.raiz == nullptr;
}

bool esNodoVacio(NodoArbolBinarioBusqueda *nodo) {
    return nodo == nullptr;
}

void plantarArbolBinario(ArbolBinarioBusqueda &arbol,const ArbolBinarioBusqueda &izq,
                        const ElementoArbolBinarioBusqueda &elemento,const ArbolBinarioBusqueda &der) {
    plantarNodoArbolBinario(arbol.raiz,izq.raiz,elemento,der.raiz);
}

void plantarNodoArbolBinario(NodoArbolBinarioBusqueda *&nodo,NodoArbolBinarioBusqueda *izq,
                                    const ElementoArbolBinarioBusqueda &elemento,NodoArbolBinarioBusqueda *der) {
    NodoArbolBinarioBusqueda *nuevo = new NodoArbolBinarioBusqueda;
    nuevo->der = der;
    nuevo->izq = izq;
    nuevo->elemento = elemento;
    nodo = nuevo;
}

void imprimirNodo(NodoArbolBinarioBusqueda *nodo) {
    cout<<setw(5)<<left<<nodo->elemento.codAlmacen;
}

void recorrerPreOrder(const ArbolBinarioBusqueda &arbol) {
    recorrerPreOrderRecursivo(arbol.raiz);
}

void recorrerPreOrderRecursivo(NodoArbolBinarioBusqueda *nodo) {
    if (!esNodoVacio(nodo)) {
        imprimirNodo(nodo);
        recorrerPreOrderRecursivo(nodo->izq);
        recorrerPreOrderRecursivo(nodo->der);
    }
}

void recorrerInOrder(const ArbolBinarioBusqueda &arbol) {
    recorrerInOrderRecursivo(arbol.raiz);
}

void recorrerInOrderRecursivo(NodoArbolBinarioBusqueda *nodo) {
    if (!esNodoVacio(nodo)) {
        recorrerInOrderRecursivo(nodo->izq);
        imprimirNodo(nodo);
        recorrerInOrderRecursivo(nodo->der);
    }
}

void recorrerPostOrder(const ArbolBinarioBusqueda &arbol) {
    recorrerPostOrderRecursivo(arbol.raiz);
}

void recorrerPostOrderRecursivo(NodoArbolBinarioBusqueda *nodo) {
    if (!esNodoVacio(nodo)) {
        recorrerPostOrderRecursivo(nodo->izq);
        recorrerPostOrderRecursivo(nodo->der);
        imprimirNodo(nodo);
    }
}

int numeroHojas(const ArbolBinarioBusqueda &arbol) {
    return numeroHojasRecursivo(arbol.raiz);
}

int numeroHojasRecursivo(NodoArbolBinarioBusqueda *nodo) {
    if (esNodoVacio(nodo)) {
        return 0;
    }else if (esNodoVacio(nodo->izq) && esNodoVacio(nodo->der)) {
        return 1;
    }else {
        return numeroHojasRecursivo(nodo->izq) + numeroHojasRecursivo(nodo->der);
    }
}

int numeroNodos(const ArbolBinarioBusqueda &arbol) {
    return numeroNodosRecursivo(arbol.raiz);
}

int numeroNodosRecursivo(NodoArbolBinarioBusqueda *nodo) {
    if (esNodoVacio(nodo))
        return 0;
    else
        return 1 + numeroNodosRecursivo(nodo->izq) + numeroNodosRecursivo(nodo->der);
}

int maximo(int num1,int num2) {
    return (num1 >= num2) ? num1 : num2;
}

int altura(const ArbolBinarioBusqueda &arbol) {
    return alturaRecursivo(arbol.raiz);
}

int alturaRecursivo(NodoArbolBinarioBusqueda *nodo) {
    if (esNodoVacio(nodo)) {
        return 0;
    }else if (nodo->izq == nullptr && nodo->der==nullptr) {
        return 0;
    }else {
        return 1 + maximo(alturaRecursivo(nodo->izq),alturaRecursivo(nodo->der));
    }
}

bool esEquilibrado(const ArbolBinarioBusqueda &arbol) {
    return esEquilibradoRecursivo(arbol.raiz);
}

bool esEquilibradoRecursivo(NodoArbolBinarioBusqueda *nodo) {
    if (esNodoVacio(nodo)) {
        return true;
    }else {
        int alturaIzq = alturaRecursivo(nodo->izq);
        int alturaDer = alturaRecursivo(nodo->der);
        int diferencia = abs(alturaIzq-alturaDer);
        return diferencia<=1 && esEquilibradoRecursivo(nodo->izq) && esEquilibradoRecursivo(nodo->der);
    }
}

void destruirArbolBinario(ArbolBinarioBusqueda &arbol) {
    destruirRecursivo(arbol.raiz);
    arbol.raiz = nullptr;
}

void destruirRecursivo(NodoArbolBinarioBusqueda *nodo) {
    if (!(esNodoVacio(nodo))) {
        destruirRecursivo(nodo->izq);
        destruirRecursivo(nodo->der);
        delete nodo;
    }
}










