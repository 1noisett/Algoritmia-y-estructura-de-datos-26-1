#include <iostream>
#include "BibliotecaFunciones/lista.h"
#include "BibliotecaFunciones/listaFunciones.h"
using namespace std;

/*
17 Messala Rojo
4 Ben-Hur Azul
12 Artax Verde
7 Drusus Negro
*/

void reordenarLista(Lista &listaTAD) {
    NodoLista *nuevaCabezaPar = nullptr;
    NodoLista *nuevaColaPar = nullptr;
    NodoLista *nuevaCabezaImpar = nullptr;
    NodoLista *nuevaColaImpar = nullptr;

    NodoLista *actual = listaTAD.inicio;
    while (actual) {
        // Guardamos el siguiente nodo antes de desconectar el actual
        NodoLista *nodoSig = actual->siguiente;
        // Desconectamos el nodo actual
        actual->siguiente = nullptr;
        // Evaluamos si es par o impar
        if (actual->elemento.id % 2 == 0) {
            if (nuevaCabezaPar == nullptr) {
                nuevaCabezaPar = nuevaColaPar = actual;
            }else {
                nuevaColaPar->siguiente = actual;
                nuevaColaPar = actual;
            }
        }else {
            if (nuevaCabezaImpar == nullptr) {
                nuevaCabezaImpar = nuevaColaImpar = actual;
            }else {
                nuevaColaImpar->siguiente = actual;
                nuevaColaImpar = actual;
            }
        }
        actual = nodoSig;
    }

    // Unimos las sublistas
    if (nuevaCabezaPar==nullptr) {
        listaTAD.inicio = nuevaColaImpar;
    }else {
        listaTAD.inicio = nuevaCabezaPar;
        nuevaColaPar->siguiente = nuevaCabezaImpar;
    }

}

int main() {
    Lista listaTAD;
    construirLista(listaTAD);
    ElementoLista cuadriga;
    // Ingreso de datos
    while (cin>>cuadriga.id>>cuadriga.nombre>>cuadriga.equipo) {
        insertarFinal(listaTAD,cuadriga);
    }
    // Imprimir la lista
    imprimirLista(listaTAD);
    // Reordenamos la lista
    reordenarLista(listaTAD);
    cout<<"\n\n";
    // Imprimimos la lista ordenada
    imprimirLista(listaTAD);
    return 0;
}
