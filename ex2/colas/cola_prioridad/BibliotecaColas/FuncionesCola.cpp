//
// Created by Miguel on 5/17/2026.
//

#include "FuncionesCola.h"

#include <iostream>
#include <stdexcept>
#include "Cola.h"
using namespace std;

void construirCola(Cola &colaTAD) {
    colaTAD.head = nullptr;
    colaTAD.tail = nullptr;
    colaTAD.last1 = nullptr;
    colaTAD.longitud = 0;
}

bool esColaVacia(const Cola &colaTAD) {
    return colaTAD.head == nullptr;
}

int longitudCola(const Cola &colaTAD) {
    return colaTAD.longitud;
}

void encolar(Cola &colaTAD, ElementoCola &elemento) {
    NodoCola *nuevo = new NodoCola();
    nuevo->elemento = elemento;
    nuevo->siguiente = nullptr;

    if (esColaVacia(colaTAD)) {
        // caso 1: cola vacía -> el nuevo es head y tail a la vez
        colaTAD.head = colaTAD.tail = nuevo;
        if (elemento.prioridad==1) {
            colaTAD.last1 = nuevo; // si es p1, también es el último p1
        }
    }else {
        if (elemento.prioridad==1) {
            if (colaTAD.last1==nullptr) {
                // caso 2: llega p1 pero NO hay ningún p1 solo hay p2
                nuevo->siguiente = colaTAD.head;
                colaTAD.head = colaTAD.last1 =  nuevo;
            }else {
                // caso 3: llega p1 y ya hay p1s
                nuevo->siguiente = colaTAD.last1->siguiente;
                colaTAD.last1->siguiente = nuevo;

                // si el último p1 era también el final de la cola (no había p2), el nuevo pasa a ser tail
                if (colaTAD.last1==colaTAD.tail) {
                    colaTAD.tail = nuevo;
                }
                colaTAD.last1 = nuevo;
            }
        }else {
            // caso 4: llega p2 -> al final de todo, como cola normal
            colaTAD.tail->siguiente = nuevo;
            colaTAD.tail = nuevo;
        }
    }
    colaTAD.longitud++;
}

ElementoCola desencolar(Cola &colaTAD) {
    if (esColaVacia(colaTAD))
        throw std::runtime_error("Error: Intentando desencolar una cola vacia");
    NodoCola *nodoBorrar = colaTAD.head;
    ElementoCola elementoBorrar = nodoBorrar->elemento;
    colaTAD.head = nodoBorrar->siguiente;

    // el detalle: si el que sacamos era el último p1;
    // la zona p1 quedó vacía -> last1 debe volver a nullptr
    if (colaTAD.last1==nodoBorrar) {
        colaTAD.last1 = nullptr;
    }
    if (colaTAD.head==nullptr) { // cola quedó vacía
        colaTAD.tail = nullptr;
    }
    colaTAD.longitud--;
    delete nodoBorrar;
    return elementoBorrar;
}


// ElementoCola desencolar(Cola &colaTAD) {
//     if (esColaVacia(colaTAD)) {
//         throw std::runtime_error("Error: Intentando desencolar una cola vacia");
//     }else {
//         NodoCola *nodoBorrar = colaTAD.head;
//         //Extraemos el dato antes de borrar el nodo
//         ElementoCola elemento = nodoBorrar->elemento;
//         colaTAD.head = nodoBorrar->siguiente;
//         if (colaTAD.head == nullptr) {
//             colaTAD.tail = nullptr;
//         }
//         colaTAD.longitud--;
//         delete nodoBorrar;
//         return elemento;
//     }
// }

void imprimir(const Cola & colaTAD) {
    if (esColaVacia(colaTAD)) {
        cout << "La cola esta vacia no se puede mostrar" << endl;
    } else {
        NodoCola * recorrido = colaTAD.head;
        int estaImprimiendoLaCabeza = 1;
        cout << "[";

        while (recorrido != nullptr) {
            /*Este artificio coloca las comas despues del inicio*/
            if ( not estaImprimiendoLaCabeza)
                cout << ", ";
            estaImprimiendoLaCabeza = 0;
            cout << recorrido->elemento.dato;
            recorrido = recorrido->siguiente;
        }
        cout << "]" << endl;
    }
}