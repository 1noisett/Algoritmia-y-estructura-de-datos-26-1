#include <iostream>

#include "BibliotecaArbolBinario/ArbolBinario.h"
#include "BibliotecaArbolBinario/FuncionesArbolBinario.h"
using namespace std;

void generarArbolCromosomaRecursivo(NodoArbolBinario *&nodo,int *arr,int idx,int n) {
    if (idx==n) return;
    // izquierda
    plantarNodoArbolBinario(nodo->izq,nullptr,{0,arr[idx]},nullptr);
    generarArbolCromosomaRecursivo(nodo->izq,arr,idx+1,n);
    // derecha
    plantarNodoArbolBinario(nodo->der,nullptr,{1,arr[idx]},nullptr);
    generarArbolCromosomaRecursivo(nodo->der,arr,idx+1,n);
}

void generarArbolCromosoma(ArbolBinario &arbol,int *arr,int n) {
    plantarNodoArbolBinario(arbol.raiz,nullptr,{0,0},nullptr);
    generarArbolCromosomaRecursivo(arbol.raiz,arr,0,n);
}

int contarCombinacionesRecursivo(NodoArbolBinario *nodo,int acumulado,int objetivo) {
    if (nodo->elemento.bit==1) {
        acumulado += nodo->elemento.valor;
    }
    if (esNodoVacio(nodo->izq) && esNodoVacio(nodo->der)) {
        return acumulado==objetivo;
    }
    return contarCombinacionesRecursivo(nodo->izq,acumulado,objetivo) + contarCombinacionesRecursivo(nodo->der,acumulado,objetivo);
}

int contarCombinaciones(ArbolBinario &arbol,int pesoBuscar) {
    return contarCombinacionesRecursivo(arbol.raiz,0,pesoBuscar);
}

int main() {
    ArbolBinario arbol;
    construir(arbol);

    int arr[] = {10,50,20,30,40};
    int n = sizeof(arr)/sizeof(arr[0]);
    generarArbolCromosoma(arbol,arr,n);

    int pesoBuscar = 70;
    cout<<contarCombinaciones(arbol,pesoBuscar)<<endl;
    return 0;
}
