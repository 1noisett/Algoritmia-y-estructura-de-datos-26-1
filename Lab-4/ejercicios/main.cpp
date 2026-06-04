#include <iostream>

#include "FuncionesDivideConquer.h"
#include "MaxSubArray.h"
#include "ContarCeros.h"
#include "ContarInversiones.h"
using namespace std;

int main() {
    // Encontrar número único
    // int arr[] = {1,1,3,3,4,5,5,7,7,8,8};
    // int n = sizeof(arr)/sizeof(arr[0]);
    // cout<<"Posición del único elemento: "<<encontrarUnico(arr, 0,n-1)<<endl;

    // Contar ceros
    // int arr[] = {1,1,1,0,0,0,0};
    // int n = sizeof(arr)/sizeof(arr[0]);
    // cout<<contarCeros(arr,n)<<endl;

    // Encontrar mínimo
    // casos extremos
    // {1, 2, 3, 4, 5}
    // int arr[] = {1, 2, 3, 4, 5};
    // int n = sizeof(arr)/sizeof(arr[0]);
    // cout<<encontrarMinimo(arr,0,n-1)<<endl;

    // Suma Contigua
    // int arr[] = {-2, -5, 6, -2, -3, 1, 5, -6};
    // int arr[] = {4,5,3};
    // int n = sizeof(arr)/sizeof(arr[0]);
    // cout<<maxSubArray(arr,0,n-1);

    // Encontrar valor máximo en un arreglo que crece y decrece
    // int arr[] = {8, 10, 20, 80, 100, 200, 400, 500, 3, 2, 1};
    // int n = sizeof(arr)/sizeof(arr[0]);
    // cout<<encontrarValorMax(arr,0,n-1);

    // Contar inversiones
    int arr[] = {7, 3, 5, 1, 6, 2, 4};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout<<mergeSort(arr,0,n-1);
    return 0;
}