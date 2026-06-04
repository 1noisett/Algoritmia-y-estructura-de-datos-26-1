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
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = sizeof(arr)/sizeof(arr[0]);
    int numEncontrar = 2;
    int indice = binarySearch(arr,0,n-1,numEncontrar);
    cout << indice << endl;

    // 2. MERGE SORT
    // int arreglo[] = {90,65,7,305,120,110,8};
    // int n = sizeof(arreglo)/sizeof(arreglo[0]);
    // imprimeArreglo(arreglo, n);
    // ordenamos el arreglo con complejidad n*log(n)
    // cout<<endl; cout<<"Ordenamos el arreglo usando Merge Sort con complejidad n*log(n)"<<endl;
    // mergeSort(arreglo, 0, n-1);
    // imprimimos el arreglo
    cout<<endl;
    imprimeArreglo(arr, n);
    return 0;
}
