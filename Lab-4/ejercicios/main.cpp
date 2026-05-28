#include <iostream>

#include "FuncionesDivideConquer.h"
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
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout<<encontrarMinimo(arr,0,n-1)<<endl;
    return 0;
}
