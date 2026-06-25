#include <iostream>
#include "BibliotecaArbolBinario/ArbolBinario.h"
#include "BibliotecaArbolBinario/FuncionesArbolBinario.h"
using namespace std;

// NodoArbolBinario *generarArbolCromosomaRecursivo(int *arr,int n,int nivel,int bit) {
//     NodoArbolBinario *nodo = new NodoArbolBinario;
//     nodo->elemento.bit = bit;
//     nodo->elemento.valor = (nivel==0) ? 0 : arr[nivel-1];
//
//     if (nivel==n) {
//         nodo->izq = nullptr;
//         nodo->der = nullptr;
//     }else {
//         // cuelga dos hijos un nivel más abajo: izq (bit 0) y der (bit 1)
//         nodo->izq = generarArbolCromosomaRecursivo(arr,n,nivel+1,0);
//         nodo->der = generarArbolCromosomaRecursivo(arr,n,nivel+1,1);
//     }
//     return nodo;
// }
//
// void generarArbolCromosoma(ArbolBinario &arbol,int *arr,int n) {
//     arbol.raiz = generarArbolCromosomaRecursivo(arr,n,0,0);
// }

void generarArbolCromosoma(NodoArbolBinario *&nodo,int *arr,int idx,int n) {
    if (idx==n) return;
    // izquierda
    plantarNodoArbolBinario(nodo->izq,nullptr,{0,arr[idx]},nullptr);
    generarArbolCromosoma(nodo->izq,arr,idx+1,n);
    // derecha
    plantarNodoArbolBinario(nodo->der,nullptr,{1,arr[idx]},nullptr);
    generarArbolCromosoma(nodo->der,arr,idx+1,n);
}

void generarArbolCromosoma(ArbolBinario &arbol,int *arr,int n) {
    // crea la raíz, sin hijos todavía
    plantarNodoArbolBinario(arbol.raiz,nullptr,{0,0},nullptr);
    generarArbolCromosoma(arbol.raiz,arr,0,n);
}


int main() {
    int arr[] = {10,50};
    int n = sizeof(arr)/sizeof(arr[0]);

    ArbolBinario arbol;
    construir(arbol);
    generarArbolCromosoma(arbol,arr,n);
    recorrerInOrder(arbol);
    cout<<endl<<numeroHojas(arbol)<<endl;
    return 0;
}
