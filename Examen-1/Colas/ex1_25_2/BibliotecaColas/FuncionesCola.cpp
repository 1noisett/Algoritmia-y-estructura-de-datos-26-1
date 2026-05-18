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

    // LÓGICA DE INSERCIÓN O(1)
    if (esColaVacia(colaTAD)) {
        // Caso 1: La cola está vacía. El nuevo nodo es head y tail.
        colaTAD.head = colaTAD.tail =nuevo;
        if (elemento.prioridad==1) {
            colaTAD.last1 = nuevo;
        }
    }else {
        if (elemento.prioridad==1) {
            // Caso 2: Ingresa un cliente Preferente (P1)
            if (colaTAD.last1 == nullptr) {
                // Subcaso 2.1: Hay clientes P2, pero no hay ningún P1.
                // Insertamos al inicio de la cola (nuevo head)
                nuevo->siguiente = colaTAD.head;
                colaTAD.head = colaTAD.last1 = nuevo;
            }else {
                // Subcaso 2.2: Ya existe al menos un P1.
                // Insertamos justo después del último P1 conocido (last1)
                nuevo->siguiente = colaTAD.last1->siguiente;
                colaTAD.last1->siguiente = nuevo;

                // Si last1 era también el final de la cola (no había P2),
                // actualizamos tail para que apunte al nuevo fin.
                if (colaTAD.last1 == colaTAD.tail) {
                    colaTAD.tail = nuevo;
                }
                colaTAD.last1 = nuevo;
            }
        }else {
            // Caso 3: Ingresa un cliente Regular (P2)
            // Simplemente se añade al final de la cola global (tail).
            colaTAD.tail->siguiente = nuevo;
            colaTAD.tail = nuevo;
        }
    }
    colaTAD.longitud++;
}

ElementoCola desencolar(Cola &colaTAD) {
    if (esColaVacia(colaTAD)) {
        throw std::runtime_error("Error: Intentando desencolar una cola vacia");
    }else {
        // LÓGICA DE ATENCIÓN O(1): Siempre sale el head (P1 va antes que P2)
        NodoCola *nodoBorrar = colaTAD.head;
        ElementoCola elementoBorrar = nodoBorrar->elemento;

        colaTAD.head = nodoBorrar->siguiente;

        // Si el elemento que acabamos de sacar era el ÚLTIMO P1 en la cola
        if (colaTAD.last1 == nodoBorrar) {
            colaTAD.last1 = nullptr; // La sección P1 queda vacía
        }

        if (colaTAD.head==nullptr) {
            colaTAD.tail = nullptr;
        }

        colaTAD.longitud--;
        delete nodoBorrar;
        return elementoBorrar;
    }
}

void imprimir(const Cola & colaTAD) {
    cout << "Estado: [P1:";

    NodoCola* actual = colaTAD.head;

    // Imprimimos la sección P1
    while (actual && actual->elemento.prioridad == 1) {
        cout << " " << actual->elemento.id;
        actual = actual->siguiente;
    }

    cout << "] [P2:";

    // El puntero "recorrido" ya está posicionado en el primer P2
    while (actual) {
        cout << " " << actual->elemento.id;
        actual = actual->siguiente;
    }

    cout << "]" << endl;
}