#include <iostream>

#include "BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h"
using namespace std;

void generarArbolBalRecursivo(NodoArbolBinarioBusqueda *&nodo,int *arr,int inicio,int fin) {
    if (inicio>fin) return;
    int medio = inicio + (fin-inicio)/2;
    ElementoArbolBinarioBusqueda e = {arr[medio]}; // creo el elemento en base al arreglo
    plantarNodoArbolBinario(nodo,nullptr,e,nullptr); // planto el nodo
    generarArbolBalRecursivo(nodo->izq,arr,inicio,medio-1);
    generarArbolBalRecursivo(nodo->der,arr,medio+1,fin);
}

void generarArbolBal(ArbolBinarioBusqueda &arbol,int *arr,int n) {
    generarArbolBalRecursivo(arbol.raiz,arr,0,n-1);
}


int main() {
    ArbolBinarioBusqueda arbol;
    construir(arbol);

    int arr[] = {2,4,6,8,10,12,14};
    int n = sizeof(arr)/sizeof(arr[0]);
    generarArbolBal(arbol,arr,n);

    recorrerPreOrder(arbol);
    return 0;
}
