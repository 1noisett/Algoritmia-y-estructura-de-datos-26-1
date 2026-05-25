#include <iostream>

#include "FuncionesDivideAndConquer.h"
using namespace std;

/*
 * El concepto tiene su origen en una estrategia militar romana del siglo IV a.C.
 * Dividir el problema principal en instancias mucho más pequeñas
 * Resolver cada una de esas instancias pequeñas de forma independiente
 * Combinar todas esas pequeñas soluciones para resolver el problema original
 */

int main() {
    // 1. BINARY SEARCH
    // int array[] = {1,2,3,4,5,6,7,8,9,10};
    // int n = sizeof(array)/sizeof(array[0]);
    // int numEncontrar = 4;
    // int indice = binarySearch(array,n,numEncontrar);
    // cout << indice << endl;

    // 2. MERGE SORT
    int arreglo[] = {90,65,7,305,120,110,8};
    int n = sizeof(arreglo)/sizeof(arreglo[0]);
    imprimeArreglo(arreglo, n);
    // ordenamos el arreglo con complejidad n*log(n)
    cout<<endl; cout<<"Ordenamos el arreglo usando Merge Sort con complejidad n*log(n)"<<endl;
    mergeSort(arreglo, 0, n-1);
    // imprimimos el arreglo
    cout<<endl;
    imprimeArreglo(arreglo, n);
    return 0;
}
