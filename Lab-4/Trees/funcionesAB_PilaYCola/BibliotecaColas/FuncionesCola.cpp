//
// Created by Miguel on 5/17/2026.
//

#include "FuncionesCola.h"

#include <iostream>
#include <stdexcept>
#include "Cola.h"
#include "../BibliotecaArbolBinario/NodoArbolBinario.h"
using namespace std;

void construirCola(Cola &colaTAD) {
    colaTAD.inicio = nullptr;
    colaTAD.fin = nullptr;
    colaTAD.longitud = 0;
}

bool esColaVacia(const Cola &colaTAD) {
    return colaTAD.inicio == nullptr;
}

int longitudCola(const Cola &colaTAD) {
    return colaTAD.longitud;
}

void encolar(Cola &colaTAD, NodoArbolBinario *elemento) {
    NodoCola *nuevo = new NodoCola();
    nuevo->nodo = elemento;

    if (esColaVacia(colaTAD)) {
        colaTAD.inicio = colaTAD.fin = nuevo;
    }else {
        colaTAD.fin->siguiente = nuevo;
        colaTAD.fin = nuevo;
    }
    colaTAD.longitud++;
}

NodoArbolBinario *desencolar(Cola &colaTAD) {
    if (esColaVacia(colaTAD)) {
        throw std::runtime_error("Error: Intentando desencolar una cola vacia");
    }else {
        NodoCola *nodoBorrar = colaTAD.inicio;
        //Extraemos el dato antes de borrar el nodo
        NodoArbolBinario *elemento = nodoBorrar->nodo;
        colaTAD.inicio = nodoBorrar->siguiente;
        if (colaTAD.inicio == nullptr) {
            colaTAD.fin = nullptr;
        }
        colaTAD.longitud--;
        delete nodoBorrar;
        return elemento;
    }
}

void imprimir(const Cola & colaTAD) {
    if (esColaVacia(colaTAD)) {
        cout << "La cola esta vacia no se puede mostrar" << endl;
    } else {
        NodoCola * recorrido = colaTAD.inicio;
        int estaImprimiendoLaCabeza = 1;
        cout << "[";

        while (recorrido != nullptr) {
            /*Este artificio coloca las comas despues del inicio*/
            if ( not estaImprimiendoLaCabeza)
                cout << ", ";
            estaImprimiendoLaCabeza = 0;
            cout << recorrido->nodo->elemento.letra;
            recorrido = recorrido->siguiente;
        }
        cout << "]" << endl;
    }
}

void destruir(struct Cola & colaTAD) {

    while ( not esColaVacia(colaTAD)) {
        struct NodoArbolBinario * elemento = desencolar(colaTAD);
    }

    colaTAD.inicio = nullptr;
    colaTAD.fin = nullptr;
    colaTAD.longitud = 0;

}