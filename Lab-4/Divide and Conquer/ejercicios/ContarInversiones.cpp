//
// Created by Miguel Bazan on 3/06/26.
//

#include "ContarInversiones.h"

int mergeSort(int *arr, int inicio, int fin) {
    if (inicio == fin) return 0;
    int medio = inicio + (fin - inicio)/2;
    int inv = 0;

    inv += mergeSort(arr,inicio,medio);
    inv += mergeSort(arr,medio+1,fin);
    inv += merge(arr,inicio,medio,fin);
    return inv;
}

int merge(int *arr,int inicio,int medio,int fin) {
    int n = fin-inicio+1;
    int temp[n];

    int i = inicio;
    int j = medio+1;
    int k = 0;
    int inv = 0;

    while (i<=medio && j<=fin) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            i++;
        }else {
            temp[k] = arr[j];
            j++;
            inv += medio - i + 1;
        }
        k++;
    }

    while (i <= medio) {
        temp[k] = arr[i];
        i++;
        k++;
    }

    while (j <= fin) {
        temp[k] = arr[j];
        j++;
        k++;
    }

    for (int x = 0; x < k; ++x) {
        arr[inicio + x] = temp[x];
    }

    return inv;
}
