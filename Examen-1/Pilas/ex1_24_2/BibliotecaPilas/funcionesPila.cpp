//
// Created by Miguel on 5/3/2026.
//
#include "funcionesPila.h"
#include <iostream>
#include "Pila.h"
using namespace std;

void construirPila(Pila &pilaTAD) {
    pilaTAD.inicio = nullptr;
    pilaTAD.longitud = 0;
}

bool esPilaVacia(Pila &pilaTAD) {
    return pilaTAD.inicio == nullptr;
}

int longitudPila(Pila &pilaTAD) {
    return pilaTAD.longitud;
}

ElementoPila cima(Pila &pilaTAD) {
    if (esPilaVacia(pilaTAD)) {
        cout<<"La pila esta vacía, por lo tanto no tiene cima"<<endl;
        exit(12);
    }
    return pilaTAD.inicio->elemento;
}

void apilar(Pila &pilaTAD,const ElementoPila &elemento) {
    NodoPila *nuevoNodo = new NodoPila();
    nuevoNodo->elemento = elemento;
    nuevoNodo->siguiente = pilaTAD.inicio;
    pilaTAD.inicio = nuevoNodo;
    pilaTAD.longitud++;
}

ElementoPila desapilar(Pila &pilaTAD) {
    NodoPila *nodoDesapilar = pilaTAD.inicio;
    pilaTAD.inicio = nodoDesapilar->siguiente;
    ElementoPila elemento = nodoDesapilar->elemento;
    pilaTAD.longitud--;
    delete nodoDesapilar;
    return elemento;
}

void destruirPila(Pila &pilaTAD) {
    NodoPila *actual = pilaTAD.inicio;
    while (actual) {
        NodoPila *nodoEliminar = actual;
        actual = actual->siguiente;
        delete nodoEliminar;
    }
    pilaTAD.inicio = nullptr;
    pilaTAD.longitud = 0;
}

void imprimirPila(Pila &pilaTAD) {
    if (esPilaVacia(pilaTAD)) {
        cout<<"La pila esta vacía, no se puede imprimir"<<endl;
        return;
    }else {
        NodoPila *actual = pilaTAD.inicio;
        while (actual) {
            cout<<actual->elemento.dato<<"  ";
            actual = actual->siguiente;
        }
    }
}
