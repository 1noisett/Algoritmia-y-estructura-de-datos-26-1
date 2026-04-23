//
// Created by Miguel Bazan on 21/04/26.
//
#include "listaFunciones.h"
#include <iostream>
#include "lista.h"

using namespace std;

void construirLista(Lista &listaTAD) {
    listaTAD.inicio = nullptr;
}

bool esListaVacia(const Lista &listaTAD) {
    return listaTAD.inicio == nullptr;
}

void insertarInicio(Lista &listaTAD,const ElementoLista &elemento) {
    NodoLista *nuevo = new NodoLista;
    nuevo->elemento = elemento;
    nuevo->siguiente = listaTAD.inicio;
    listaTAD.inicio = nuevo;
}

NodoLista *obtenerUltimoNodo(Lista &listaTAD) {
    NodoLista *ptr = listaTAD.inicio;
    while (ptr->siguiente != nullptr) {
        ptr = ptr->siguiente;
    }
    return ptr;
}

void insertarFinal(Lista &listaTAD, const ElementoLista &elemento) {
    NodoLista *nuevoNodo = new NodoLista;
    nuevoNodo->elemento = elemento;
    nuevoNodo->siguiente = nullptr;

    if (listaTAD.inicio == nullptr) {
        listaTAD.inicio = nuevoNodo;
    }else {
        NodoLista *ultimoNodo = obtenerUltimoNodo(listaTAD);
        ultimoNodo->siguiente = nuevoNodo;
    }
}

// void insertarEnOrden(Lista &listaTAD,const ElementoLista &elemento) {
//     NodoLista *nuevo, *actual = listaTAD.inicio, *anterior = nullptr;
//     // Crear el nuevo nodo y asignar el elemento
//     nuevo = new NodoLista;
//     nuevo->elemento = elemento;
//     nuevo->siguiente = nullptr;
//
//     // Recorremos la lista buscando la posición correcta. Nos detenemos cuando encontramos un nodo mayor al elemento
//     while (actual and actual->elemento.dato <= elemento.dato) {
//         anterior = actual;
//         actual = actual->siguiente;
//     }
//
//     // Insertamos el nuevo nodo:
//     // el nuevo debe apuntar al nodo actual
//     nuevo->siguiente = actual;
//
//     if (anterior == nullptr)
//         listaTAD.inicio = nuevo;
//     else
//         anterior->siguiente = nuevo; // Caso general: enlazamos el nodo anterior con el nuevo
// }

// void eliminarNodo(Lista &listaTAD,const ElementoLista &elemento) {
//     NodoLista *actual = listaTAD.inicio;
//     NodoLista *anterior = nullptr;
//     while (actual and actual->elemento.dato != elemento.dato) {
//         anterior = actual;
//         actual = actual->siguiente;
//     }
//     if (actual==nullptr) return;
//
//     if (anterior==nullptr) {
//         listaTAD.inicio = actual->siguiente;
//     }else {
//         anterior->siguiente = actual->siguiente;
//     }
//     delete actual;
// }

void eliminarLista(Lista &listaTAD) {
    NodoLista *actual = listaTAD.inicio;
    // 1. Liberar la memoria de cada nodo
    while (actual) {
        NodoLista *nodoEliminar = actual;
        actual = actual->siguiente;
        delete nodoEliminar;
    }
    //2. Reiniciar el puntero de la lista para indicar que ahora esta vacía
    listaTAD.inicio = nullptr;
}

void imprimirLista(const Lista &listaTAD) {
    NodoLista *ptr = listaTAD.inicio;
    while (ptr) {
        cout << ptr->elemento.numCamiseta<<"  "<<ptr->elemento.nombre <<"  "<<ptr->elemento.posicion<<endl;
        ptr = ptr->siguiente;
    }
    cout << "nullptr"<<endl;
}