#include <iostream>

#include "BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h"
#include "BibliotecaColas/Cola.h"
#include "BibliotecaColas/FuncionesCola.h"
#include "BibliotecaPilas/funcionesPila.h"
#include "BibliotecaPilas/Pila.h"
using namespace std;

void diagonalConNodos(ArbolBinarioBusqueda &arbol) {
    Cola cola;                                  // guarda nodo
    construirCola(cola);
    encolar(cola,arbol.raiz);

    while (!esColaVacia(cola)) {
        NodoArbolBinarioBusqueda *actual = desencolar(cola); // el puntero YA es el nodo
        while (actual) {                                        // cadena derecha = misma diagonal
            cout<<actual->elemento.flag<<"-"<<actual->elemento.idServidor<<" ";
            if (!esNodoVacio(actual->izq)) encolar(cola,actual->izq);
            actual = actual->der;                               // sigo en la diagonal
        }
    }
}

int main() {
    ArbolBinarioBusqueda arbol;
    construir(arbol);
    insertar(arbol,{100,0});
    insertar(arbol,{50,0});
    insertar(arbol,{25,0});
    insertar(arbol,{75,0});
    insertar(arbol,{40,0});
    insertar(arbol,{150,0});
    insertar(arbol,{125,1});
    insertar(arbol,{175,0});
    insertar(arbol,{200,0});

    diagonalConNodos(arbol);

    return 0;
}
