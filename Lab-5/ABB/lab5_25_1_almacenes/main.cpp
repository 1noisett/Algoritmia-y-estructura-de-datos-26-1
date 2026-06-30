#include <iostream>

#include "BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h"
#include "BibliotecaColas/Cola.h"
#include "BibliotecaColas/FuncionesCola.h"
using namespace std;

// Eliminar todos los nodos que sean hijos únicos de su padre

void recorrerPorNiveles(ArbolBinarioBusqueda &arbol) {
    Cola cola;
    construirCola(cola);
    if (!esArbolVacio(arbol)) {
        encolar(cola,arbol.raiz);
        while (!esColaVacia(cola)) {
            NodoArbolBinarioBusqueda *nodo = desencolar(cola);
            imprimirNodo(nodo);
            if (!esNodoVacio(nodo->izq)) encolar(cola,nodo->izq);
            if (!esNodoVacio(nodo->der)) encolar(cola,nodo->der);
        }
    }
}


int main() {
    ArbolBinarioBusqueda arbol;
    construir(arbol);
    insertar(arbol,{100});
    insertar(arbol,{50});
    insertar(arbol,{25});
    insertar(arbol,{75});
    insertar(arbol,{30});
    insertar(arbol,{28});
    insertar(arbol,{150});
    insertar(arbol,{125});
    insertar(arbol,{175});
    insertar(arbol,{200});

    recorrerPorNiveles(arbol);

    return 0;
}
