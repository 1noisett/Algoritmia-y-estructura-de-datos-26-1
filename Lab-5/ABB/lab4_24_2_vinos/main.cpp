#include <iostream>
#include "BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h"
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

void reporteRecursivo(NodoArbolBinarioBusqueda *nodo) {
    if (!esNodoVacio(nodo)) {
        reporteRecursivo(nodo->der);
        imprimirNodo(nodo);
        reporteRecursivo(nodo->izq);
    }
}

void reporte(ArbolBinarioBusqueda &arbol) {
    reporteRecursivo(arbol.raiz);
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

    reporte(arbol);
    return 0;
}
