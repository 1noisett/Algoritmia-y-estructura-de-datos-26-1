#include <iostream>
using namespace std;

#define MAX_COL 20

int merge(int *arr,int inicio,int medio,int fin) {
    int temp[MAX_COL];

    int i = inicio;
    int j = medio + 1;
    int k = 0;
    int inversiones = 0;
    while (i<=medio && j<=fin) {
        if (arr[i]<=arr[j]) {
            temp[k] = arr[i]; i++;
        }else {
            temp[k] = arr[j]; j++;
            inversiones += medio - i + 1;
        }
        k++;
    }
    while (i<=medio) {
        temp[k] = arr[i]; i++; k++;
    }
    while (j<=fin) {
        temp[k] = arr[j]; j++; k++;
    }
    for (int x = 0; x < k; ++x) {
        arr[inicio+x] = temp[x];
    }
    return inversiones;
}

int mergeSort(int *arr,int inicio,int fin) {
    if (inicio==fin) return 0; // cuando el sub arreglo tiene un solo elemento [5] no existen pares de elementos
                               // por lo que el número de inversiones es 0
    int medio = inicio + (fin-inicio)/2;
    int inversiones = 0;

    inversiones += mergeSort(arr,inicio,medio);
    inversiones += mergeSort(arr,medio+1,fin);
    inversiones += merge(arr,inicio,medio,fin);
    return inversiones;
}

int main() {
    int arr[] = {10,12,14,13,11,15};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout<<mergeSort(arr,0,n-1)<<endl;
    return 0;
}
