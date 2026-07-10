#include <iostream>

#include "BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h"
#include "BibliotecaColas/Cola.h"
#include "BibliotecaColas/FuncionesCola.h"
#include "BibliotecaPilas/funcionesPila.h"
#include "BibliotecaPilas/Pila.h"
using namespace std;

void diagonalConNodos(NodoArbolBinarioBusqueda *nodo) {
    Cola cola;
    construirCola(cola);
    encolar(cola,nodo);

    while (!esColaVacia(cola)) {
        NodoArbolBinarioBusqueda *actual = desencolar(cola);
        while (actual) {
            cout<<
        }
    }
}

int main() {
    ArbolBinarioBusqueda arbol;
    construir(arbol);


    return 0;
}
