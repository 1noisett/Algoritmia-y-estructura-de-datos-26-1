#include <iostream>

#include "BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h"
using namespace std;

int main() {
    ArbolBinarioBusqueda arbol;
    construir(arbol);

    int arr[] = {2,4,6,8,10,12,14};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    return 0;
}
