#include <fstream>
#include <iostream>

#include "listasFunciones/lista.h"
#include "listasFunciones/listaFunciones.h"
using namespace std;

void reordenarLista(Lista &lista) {
    NodoLista *cabezaA = nullptr, *colaA = nullptr;
    NodoLista *cabezaG = nullptr, *colaG = nullptr;
    NodoLista *cabezaI = nullptr, *colaI = nullptr;

    NodoLista *actual = lista.inicio;
    while (actual) {
        if (actual->elemento.prioridad == 'A') {
            //Extraemos el nodo 'A' actual
            NodoLista *sigNodo = actual->siguiente;
            actual->siguiente = nullptr;

            //Lo insertamos en la sublista A
            if (cabezaA == nullptr) {
                cabezaA = colaA = actual;
            }else {
                colaA->siguiente = actual;
                colaA = actual;
            }
            actual = sigNodo;
        }else {
            //Es de prioridad 'B' o 'C'. Contamos cuantos consecutivos identicos hay
            char prioActual = actual->elemento.prioridad;
            NodoLista *inicioBloque = actual;
            NodoLista *finBloque = actual;
            int count = 1;

            //Avanzamos el puntero mientras sigan teniendo la misma prioridad
            while (finBloque->siguiente != nullptr && finBloque->siguiente->elemento.prioridad == prioActual) {
                finBloque = finBloque->siguiente;
                count++;
            }

            //Guardamos donde continúa el resto de la lista original y aislamos el bloque recorrido
            NodoLista *sigBloque = finBloque->siguiente;
            finBloque->siguiente = nullptr;

            //Clasificamos el bloque completo segun tamano
            if (count>=2) {
                if (cabezaG == nullptr) {
                    cabezaG = inicioBloque;
                    colaG = finBloque;
                }else {
                    colaG->siguiente = inicioBloque;
                    colaG = finBloque;
                }
            }else {
                if (cabezaI == nullptr) {
                    cabezaI = inicioBloque;
                    colaI = finBloque;
                }else {
                    colaI->siguiente = inicioBloque;
                    colaI = finBloque;
                }
            }
            actual = sigBloque;
        }
    }
    //Concatenacion
    lista.inicio = cabezaA;
    colaA->siguiente = cabezaG;
    colaG->siguiente = cabezaI;
    colaI->siguiente = nullptr;
}

int main() {
    Lista lista;
    construirLista(lista);

    //Ingreso de datos
    ifstream input("input.txt");
    ElementoLista elemento;
    while (true) {
        input>>elemento.codigo;
        if (input.eof()) break;
        input>>elemento.cantidad>>elemento.prioridad;
        insertarFinal(lista,elemento);
    }
    imprimirLista(lista);
    //reordenar lista
    reordenarLista(lista);
    //imprimir lista ordenada
    cout<<endl;
    imprimirLista(lista);
    return 0;
}
