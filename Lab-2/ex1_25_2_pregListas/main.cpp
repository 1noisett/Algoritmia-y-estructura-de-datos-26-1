#include <fstream>
#include <iostream>
#include "BibliotecaFunciones/lista.h"
#include "BibliotecaFunciones/listaFunciones.h"

using namespace std;

void reordenarLista(Lista &listaTAD) {
    NodoLista *cabezaA = nullptr, *colaA = nullptr;
    NodoLista *cabezaB = nullptr, *colaB = nullptr;
    NodoLista *cabezaC = nullptr, *colaC = nullptr;
    NodoLista *actual = listaTAD.inicio;
    // PASO 1: REPARTIR LOS NODOS EN LAS CAJAS
    while (actual) {
        NodoLista *sig = actual->siguiente;
        actual->siguiente = nullptr;

        if (actual->elemento.tipo_produccion == 'A') {
            if (cabezaA == nullptr) {
                cabezaA = colaA = actual;
            }else {
                colaA->siguiente = actual;
                colaA = actual;
            }
        }else if (actual->elemento.tipo_produccion == 'B') {
            if (cabezaB == nullptr) {
                cabezaB = colaB = actual;
            }else {
                colaB->siguiente = actual;
                colaB = actual;
            }
        }else if (actual->elemento.tipo_produccion == 'C') {
            if (cabezaC == nullptr) {
                cabezaC = colaC = actual;
            }else {
                colaC->siguiente = actual;
                colaC = actual;
            }
        }
        actual = sig;
    }
    // PASO 2: ARMAR EL CICLO A -> B -> C -> A -> B -> C
    NodoLista *nuevaCabeza = nullptr, *nuevaCola = nullptr;

    while (cabezaA or cabezaB or cabezaC) {
        //Turno de sacar un nodo A
        if (cabezaA!=nullptr) {
            if (nuevaCabeza==nullptr) {
                nuevaCabeza = nuevaCola = cabezaA;
            }else {
                nuevaCola->siguiente = cabezaA;
                nuevaCola = cabezaA;
            }
            cabezaA = cabezaA->siguiente; //Avanzamos al sig en la fila A
        }

        //Turno de sacar un nodo B
        if (cabezaB!=nullptr) {
            if (nuevaCabeza==nullptr) {//No hubo nodo A
                nuevaCabeza = nuevaCola = cabezaB;
            }else {
                nuevaCola->siguiente = cabezaB;
                nuevaCola = cabezaB;
            }
            cabezaB = cabezaB->siguiente; //Avanzamos al sig en la fila B
        }
        //Turno de sacar un nodo C
        if (cabezaC!=nullptr) {
            if (nuevaCabeza==nullptr) {//No hubo ni nodo A ni B
                nuevaCabeza = nuevaCola = cabezaC;
            }else {
                nuevaCola->siguiente = cabezaC;
                nuevaCola = cabezaC;
            }
            cabezaC = cabezaC->siguiente;//Avanzamos al sig en la fila C
        }
    }

    listaTAD.inicio = nuevaCabeza;
}

int main() {
    Lista lista;
    construirLista(lista);
    ifstream input("input.txt");
    while (true) {
        ElementoLista elemento;
        input>>elemento.id>>elemento.tipo_produccion;
        if (input.eof()) break;
        insertarFinal(lista, elemento);
    }
    imprimirLista(lista);
    // Reordenar lista
    reordenarLista(lista);
    cout<<endl<<endl;
    imprimirLista(lista);
    return 0;
}
