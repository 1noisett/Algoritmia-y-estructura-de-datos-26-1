#include <iostream>

#include "BibliotecaArbolBinario/ArbolBinario.h"
#include "BibliotecaArbolBinario/FuncionesArbolBinario.h"
using namespace std;

int main() {
    ArbolBinario arbol;
    construir(arbol);

    int arr[] = {10,50};
    int n = sizeof(arr)/sizeof(arr[0]);
    return 0;
}
