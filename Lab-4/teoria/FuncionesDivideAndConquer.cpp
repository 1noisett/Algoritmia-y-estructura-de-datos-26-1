//
// Created by Miguel on 5/24/2026.
//

#include "FuncionesDivideAndConquer.h"
#include <iostream>

int binarySearch(int *arr,int inicio,int fin,int num) {
    if (inicio == fin) return arr[inicio] == num ? inicio : -1;

    int medio = (inicio + fin)/2;

    if (arr[medio] < num) {
        return binarySearch(arr,medio+1,fin,num);
    }else {
        return binarySearch(arr,inicio,medio,num);
    }
}

void mergeSort(int *arr,int inicio, int fin) {
    // caso base
    if (inicio==fin) return;
    // parte recursiva
    int medio = (inicio + fin)/2;
    mergeSort(arr,inicio,medio); // izq arreglo
    mergeSort(arr,medio+1,fin); // der arreglo
    merge(arr,inicio,medio,fin); // fusionar
}

void merge(int *arr, int inicio, int medio, int fin) {
    int n = fin - inicio + 1;
    int temp[n];

    int i = inicio;
    int j = medio + 1;
    int k = 0;

    while (i<=medio && j <=fin) {
        if (arr[i]>arr[j]) {
            temp[k] = arr[j];
            j++;
        }else {
            temp[k] = arr[i];
            i++;
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
}



void imprimeArreglo(int arreglo[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arreglo[i] << ", ";
    }
}