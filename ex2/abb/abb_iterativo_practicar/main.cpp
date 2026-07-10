#include <iostream>

#include "BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h"
#include "BibliotecaColas/Cola.h"
#include "BibliotecaColas/FuncionesCola.h"
#include "BibliotecaPilas/funcionesPila.h"
#include "BibliotecaPilas/Pila.h"
using namespace std;

// RECORRER PRE ORDER
void recorrerPreOrderIterativo(ArbolBinarioBusqueda &arbol) {
    Pila pila;
    construirPila(pila);
    apilar(pila,arbol.raiz);

    while (!esPilaVacia(pila)) {
        NodoArbolBinarioBusqueda *nodo = desapilar(pila);
        imprimirNodo(nodo);

        if (!esNodoVacio(nodo->der)) apilar(pila,nodo->der);
        if (!esNodoVacio(nodo->izq)) apilar(pila,nodo->izq);
    }
}

// RECORRER IN ORDER
void recorrerInOrderIterativo(ArbolBinarioBusqueda &arbol) {
    Pila pila;
    construirPila(pila);
    NodoArbolBinarioBusqueda *actual = arbol.raiz;
    while (actual || !esPilaVacia(pila)) {
        while (actual) {
            apilar(pila,actual);
            actual = actual->izq;
        }
        actual = desapilar(pila);
        imprimirNodo(actual);
        actual = actual->der;
    }
}

// RECORRER POST ORDER
void recorrerPostOrderIterativo(ArbolBinarioBusqueda &arbol) {
    Pila p1,p2;
    construirPila(p1);
    construirPila(p2);
    apilar(p1,arbol.raiz);
    while (!esPilaVacia(p1)) {
        NodoArbolBinarioBusqueda *nodo = desapilar(p1);
        apilar(p2,nodo);
        if (!esNodoVacio(nodo->izq)) apilar(p1,nodo->izq);
        if (!esNodoVacio(nodo->der)) apilar(p1,nodo->der);
    }
    while (!esPilaVacia(p2)) {
        imprimirNodo(desapilar(p2));
    }
}

// RECORRER POR NIVELES
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

// RECORRER POR NIVELES INVERSO (amplitud inversa)
// Estrategia: recorrido por niveles con cola, pero en vez de imprimir cada
// nodo se apila. Al vaciar la pila al final, el orden queda invertido:
// los niveles salen de abajo hacia arriba. Se encola der,izq para que,
// tras la inversion de la pila, cada nivel salga de izq a der.
// Cada nodo pasa una vez por la cola y una por la pila -> O(N).
void recorrerPorNivelesInverso(ArbolBinarioBusqueda &arbol) {
    if (esArbolVacio(arbol)) return;

    Cola cola;
    Pila pila;
    construirCola(cola);
    construirPila(pila);

    encolar(cola,arbol.raiz);
    while (!esColaVacia(cola)) {
        NodoArbolBinarioBusqueda *nodo = desencolar(cola);
        apilar(pila,nodo);                  // se imprime al final, invertido
        if (!esNodoVacio(nodo->der)) encolar(cola,nodo->der);
        if (!esNodoVacio(nodo->izq)) encolar(cola,nodo->izq);
    }
    while (!esPilaVacia(pila)) {
        imprimirNodo(desapilar(pila));
    }
}


// RECORRER ZIG ZAG
void recorrerZigZag(ArbolBinarioBusqueda &arbol) {
    Pila pilaActual,pilaSig;
    construirPila(pilaActual);
    construirPila(pilaSig);

    apilar(pilaActual,arbol.raiz);        // apilo la raíz del árbol
    bool izqADer = true;                    // el nivel 1 se lee de izq a der
    int nivel = 1;
    while (!esPilaVacia(pilaActual)) {  // una vuelta = un nivel completo
        cout<<"Nivel "<<nivel<<": ";
        while (!esPilaVacia(pilaActual)) { // procesa todo el nivel actual
            NodoArbolBinarioBusqueda *nodo = desapilar(pilaActual);
            cout<<nodo->elemento.numero<<" ";

            if (izqADer) {
                // este nivel salió izq->der; para el siguiente que salga der->izq, apilo izq primero(la pila lo invertira)
                if (!esNodoVacio(nodo->izq)) apilar(pilaSig,nodo->izq);
                if (!esNodoVacio(nodo->der)) apilar(pilaSig,nodo->der);
            }else {
                // este nivel salió der->izq; apilo der primero para que el siguiente vuelva a salir izq->der
                if (!esNodoVacio(nodo->der)) apilar(pilaSig,nodo->der);
                if (!esNodoVacio(nodo->izq)) apilar(pilaSig,nodo->izq);
            }
        }
        cout<<endl;
        // intercambio de pilas: la vacia pasa a acumular, la llena a procesar
        // copiar la pila (puntero inicio + longitud) es seguro
        // no duplica nodos, solo cambia de dueño
        Pila temp = pilaActual;
        pilaActual = pilaSig;
        pilaSig = temp;
        izqADer = !izqADer;
        nivel++;
    }
}

// RECORRER DIAGONAL


int main() {
    ArbolBinarioBusqueda arbol;
    construir(arbol);
    // PRACTICAR RECORRIDOS ITERATIVOS
    // insertar(arbol,{30});
    // insertar(arbol,{20});
    // insertar(arbol,{15});
    // insertar(arbol,{22});
    // insertar(arbol,{50});
    // insertar(arbol,{55});
    // insertar(arbol,{40});
    // insertar(arbol,{60});
    // recorrerPreOrderIterativo(arbol);
    // cout<<endl<<endl;
    // recorrerInOrderIterativo(arbol);
    // cout<<endl<<endl;
    // recorrerPostOrderIterativo(arbol);
    // cout<<endl<<endl;
    // recorrerPorNiveles(arbol);

    // RECORRER ZIG ZAG LAB 5 2026-1
    // insertar(arbol,{9});
    // insertar(arbol,{4});
    // insertar(arbol,{1});
    // insertar(arbol,{6});
    // insertar(arbol,{14});
    // insertar(arbol,{11});
    // insertar(arbol,{16});
    // insertar(arbol,{19});
    // recorrerZigZag(arbol);

    // RECORRER POR NIVELES INVERSO (amplitud inversa)
    insertar(arbol,{9});
    insertar(arbol,{4});
    insertar(arbol,{1});
    insertar(arbol,{6});
    insertar(arbol,{14});
    insertar(arbol,{11});
    insertar(arbol,{16});
    insertar(arbol,{19});
    recorrerPorNiveles(arbol);          // esperado: 9  4 14  1 6 11 16  19
    cout<<endl<<endl;
    recorrerPorNivelesInverso(arbol);   // esperado: 19  1 6 11 16  4 14  9


    return 0;
}
