#include <iostream>
#include "BibliotecaArbolBinario/ArbolBinario.h"
#include "BibliotecaArbolBinario/FuncionesArbolBinario.h"
using namespace std;

int main() {
    int arr[] = {10,50,20,30,40};
    int n = sizeof(arr)/sizeof(arr[0]);

    ArbolBinario arbol;
    ArbolBinario arbolVacio;
    construir(arbol);
    construir(arbolVacio);

    plantarArbolBinario(arbol,arbolVacio,{0,0},arbolVacio);
    return 0;
}
