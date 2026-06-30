#include <iostream>
#include "BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h"
#include "BibliotecaPilas/funcionesPila.h"
#include "BibliotecaPilas/Pila.h"
using namespace std;

void ingresarLoteRecursivo(NodoArbolBinarioBusqueda *&nodo,const ElementoArbolBinarioBusqueda &elemento) {
    if (esNodoVacio(nodo)) {
        plantarNodoArbolBinarioRecursivo(nodo,nullptr,elemento,nullptr);
    }else {
        int cmp = comparaElementos(nodo->elemento.year,elemento.year);
        if (cmp==1) {
            ingresarLoteRecursivo(nodo->izq,elemento);
        }else if (cmp==-1) {
            ingresarLoteRecursivo(nodo->der,elemento);
        }else {
            // actualizamos la cantidad
            nodo->elemento.cantidad += elemento.cantidad;
        }
    }
}

void ingresaLote(ArbolBinarioBusqueda &arbol,const ElementoArbolBinarioBusqueda &elemento) {
    ingresarLoteRecursivo(arbol.raiz,elemento);
}

NodoArbolBinarioBusqueda *buscarNodoIterativo(ArbolBinarioBusqueda &arbol,int year) {
    NodoArbolBinarioBusqueda *actual = arbol.raiz;
    while (actual && actual->elemento.year!=year) {
        if (comparaElementos(actual->elemento.year,year)==1) {
            actual = actual->izq;
        }else {
            actual = actual->der;
        }
    }
    return actual;
}

void generarReporte(ArbolBinarioBusqueda &arbol) {
    if (esArbolVacio(arbol)) return;

    Pila pila;
    construirPila(pila);
    ElementoPila elemento; // aquí guardaré cada dato(año+cantidad) que desapile
    NodoArbolBinarioBusqueda *actual = arbol.raiz;
    while (true) {
        // (1) bajar todo a la derecha, apilando cada nodo que obtengo
        // como voy a la derecha apilo años de menor a mayor -> el mayor queda en la cima
        while (actual) {
            ElementoPila e;
            e.year = actual->elemento.year;
            e.cantidad = actual->elemento.cantidad;
            apilar(pila,e);
            actual = actual->der; // sigo bajando a la derecha
        }
        // al salir del while actual es nullptr y en la cima está el año más grande
        // (2) desapilar e imprimir el de la cima(el mayor) -> orden descendente
        elemento = desapilar(pila);
        cout<<elemento.year<<"-"<<elemento.cantidad<<" ";
        // (3) moverme al subárbol izquierdo del nodo que acabo de imprimir
        actual = buscarNodoIterativo(arbol,elemento.year)->izq;
        // si la pila esta vacía y tampoco hay subárbol izquierdo por explorar, terminé todos los nodos
        if (esPilaVacia(pila) && actual==nullptr) break;
    }
    cout<<endl;
}


int main() {
    ArbolBinarioBusqueda arbol;
    construir(arbol);
    ingresaLote(arbol,{2018,100});
    ingresaLote(arbol,{2011,150});
    ingresaLote(arbol,{2010,175});
    ingresaLote(arbol,{2017,25});
    ingresaLote(arbol,{2022,50});
    ingresaLote(arbol,{2019,125});
    ingresaLote(arbol,{2023,200});
    ingresaLote(arbol,{2020,75});

    generarReporte(arbol);
    return 0;
}
