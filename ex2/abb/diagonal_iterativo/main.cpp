#include <iostream>

#include "BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h"
#include "BibliotecaColas/Cola.h"
#include "BibliotecaColas/FuncionesCola.h"
#include "BibliotecaPilas/funcionesPila.h"
#include "BibliotecaPilas/Pila.h"
using namespace std;

void recorrerDiagonal(ArbolBinarioBusqueda &arbol) {
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

void recorrerDiagonalInversa(ArbolBinarioBusqueda &arbol) {
    Cola cola;
    Pila pila;
    construirCola(cola);
    construirPila(pila);
    encolar(cola,arbol.raiz);
    // mismo recorrido diagonal, pero en vez de imprimir -> apilar
    while (!esColaVacia(cola)) {
        NodoArbolBinarioBusqueda *actual = desencolar(cola);
        while (actual) {
            apilar(pila,actual);
            if (!esNodoVacio(actual->izq)) encolar(cola,actual->izq);
            actual = actual->der;
        }
    }
    // la pila devuelve todo el recorrido invertido
    while (!esPilaVacia(pila)) {
        NodoArbolBinarioBusqueda *nodo = desapilar(pila);
        cout<<nodo->elemento.flag<<"-"<<nodo->elemento.idServidor<<" ";
    }
    cout<<endl;
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

    recorrerDiagonal(arbol);
    cout<<endl<<endl;
    recorrerDiagonalInversa(arbol);
    cout<<endl;

    

    return 0;
}




// ============================================================================
// VERSION SIN NODOS (examen 2024-2 P3: "la pila o cola solo puede recibir
// datos mas no nodos del arbol")
//
// ESTAS FUNCIONES NO COMPILAN TODAVIA: estan escritas contra las firmas que
// tendran las bibliotecas despues de migrarlas. Cambios pendientes:
//
// BibliotecaColas/NodoCola.h:
//     struct NodoCola {
//         ElementoArbolBinarioBusqueda dato;   // antes: NodoArbolBinarioBusqueda *nodo
//         NodoCola *siguiente;
//     };
//     (ya no necesita incluir NodoArbolBinarioBusqueda.h, solo ElementoArbolBinarioBusqueda.h)
//
// BibliotecaColas/FuncionesCola.h y .cpp — nuevas firmas:
//     void encolar(Cola &colaTAD, ElementoArbolBinarioBusqueda dato);
//     ElementoArbolBinarioBusqueda desencolar(Cola &colaTAD);
//
// BibliotecaPilas/NodoPila.h:
//     struct NodoPila {
//         ElementoArbolBinarioBusqueda dato;   // antes: NodoArbolBinarioBusqueda *elemento
//         NodoPila *siguiente;
//     };
//
// BibliotecaPilas/funcionesPila.h y .cpp — nuevas firmas:
//     void apilar(Pila &pilaTAD, ElementoArbolBinarioBusqueda dato);
//     ElementoArbolBinarioBusqueda desapilar(Pila &pilaTAD);
//     (cima() tambien pasaria a devolver ElementoArbolBinarioBusqueda)
// ============================================================================

// busqueda ITERATIVA en el ABB: relocaliza el nodo de un id en O(log n).
// necesaria porque la cola ya no guarda punteros; el enunciado ademas exige
// que toda funcion invocada sea iterativa. esta si compila con la biblioteca actual.
NodoArbolBinarioBusqueda *buscarNodoIterativo(ArbolBinarioBusqueda &arbol,int idServidor) {
    NodoArbolBinarioBusqueda *actual = arbol.raiz;
    while (!esNodoVacio(actual) && actual->elemento.idServidor != idServidor) {
        if (idServidor < actual->elemento.idServidor) actual = actual->izq;
        else actual = actual->der;
    }
    return actual;
}

// diagonal SIN nodos: la cola transporta el dato {idServidor, flag}.
// al desencolar un dato, se relocaliza su nodo bajando desde la raiz (ABB).
// costo total O(n log n): una busqueda por cada inicio de diagonal.
void recorrerDiagonalSinNodos(ArbolBinarioBusqueda &arbol) {
    if (esArbolVacio(arbol)) return;
    Cola cola;                                    // cola de DATOS
    construirCola(cola);
    encolar(cola,arbol.raiz->elemento);

    while (!esColaVacia(cola)) {
        ElementoArbolBinarioBusqueda dato = desencolar(cola);
        NodoArbolBinarioBusqueda *actual = buscarNodoIterativo(arbol,dato.idServidor); // relocalizar
        while (!esNodoVacio(actual)) {            // cadena derecha = misma diagonal
            cout<<actual->elemento.flag<<"-"<<actual->elemento.idServidor<<" ";
            if (!esNodoVacio(actual->izq)) encolar(cola,actual->izq->elemento);
            actual = actual->der;
        }
    }
    cout<<endl;
}



// diagonal inversa SIN nodos: mismo recorrido pero apilando el dato COMPLETO
// (flag e id) para no tener que relocalizar de nuevo al imprimir.
// la pila invierte todo el recorrido -> sale del final hacia la raiz.
void recorrerDiagonalInversaSinNodos(ArbolBinarioBusqueda &arbol) {
    if (esArbolVacio(arbol)) return;
    Cola cola;                                    // cola de DATOS
    Pila pila;                                    // pila de DATOS
    construirCola(cola);
    construirPila(pila);
    encolar(cola,arbol.raiz->elemento);

    while (!esColaVacia(cola)) {
        ElementoArbolBinarioBusqueda dato = desencolar(cola);
        NodoArbolBinarioBusqueda *actual = buscarNodoIterativo(arbol,dato.idServidor);
        while (!esNodoVacio(actual)) {
            apilar(pila,actual->elemento);        // en vez de imprimir -> apilar
            if (!esNodoVacio(actual->izq)) encolar(cola,actual->izq->elemento);
            actual = actual->der;
        }
    }
    while (!esPilaVacia(pila)) {
        ElementoArbolBinarioBusqueda dato = desapilar(pila);
        cout<<dato.flag<<"-"<<dato.idServidor<<" ";
    }
    cout<<endl;
}
