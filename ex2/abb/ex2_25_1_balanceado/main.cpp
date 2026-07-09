#include <iostream>

#include "BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h"
using namespace std;

void arbolBalanceadoRecursivo(NodoArbolBinarioBusqueda *&nodo,int inicio,int fin,int *arr) {
    if (inicio>fin) return;
    int medio = inicio + (fin-inicio)/2;
    ElementoArbolBinarioBusqueda e = {arr[medio]};
    plantarNodoArbolBinario(nodo,nullptr,e,nullptr);
    arbolBalanceadoRecursivo(nodo->izq,inicio,medio-1,arr);
    arbolBalanceadoRecursivo(nodo->der,medio+1,fin,arr);
}

void arbolBalanceado(ArbolBinarioBusqueda &arbol,int n,int *arr) {
    arbolBalanceadoRecursivo(arbol.raiz,0,n-1,arr);
}

int main() {
    ArbolBinarioBusqueda arbol;
    construir(arbol);

    // int arr[] = {2,4,6,8,10,12,14};
    int arr[] = {-5,1,5,8,12,16,19,22,66};
    int n = sizeof(arr)/sizeof(arr[0]);
    arbolBalanceado(arbol,n,arr);
    recorrerPreOrder(arbol);
    return 0;
}
