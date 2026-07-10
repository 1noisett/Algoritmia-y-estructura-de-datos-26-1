//
// Created by Miguel on 5/17/2026.
//

#include "FuncionesCola.h"

#include <iostream>
#include <stdexcept>
#include "Cola.h"
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

void encolar(Cola &colaTAD, ElementoCola &elemento) {
    NodoCola *nuevo = new NodoCola();
    nuevo->elemento = elemento;
    nuevo->siguiente = nullptr;

    if (esColaVacia(colaTAD)) {
        colaTAD.inicio = colaTAD.fin = nuevo;
    }else {
        colaTAD.fin->siguiente = nuevo;
        colaTAD.fin = nuevo;
    }
    colaTAD.longitud++;
}

ElementoCola desencolar(Cola &colaTAD) {
    if (esColaVacia(colaTAD)) {
        throw std::runtime_error("Error: Intentando desencolar una cola vacia");
    }else {
        NodoCola *nodoBorrar = colaTAD.inicio;
        //Extraemos el dato antes de borrar el nodo
        ElementoCola elemento = nodoBorrar->elemento;
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
            cout << recorrido->elemento.dato;
            recorrido = recorrido->siguiente;
        }
        cout << "]" << endl;
    }
}