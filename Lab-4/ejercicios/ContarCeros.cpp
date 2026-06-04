//
// Created by Miguel Bazan on 2/06/26.
//

#include "ContarCeros.h"

int buscarPrimerCero(int *arr, int inicio, int fin) {
    if (inicio == fin) return inicio;

    int mid = inicio + (fin-inicio)/2;

    if (arr[mid] == 1) {
        return buscarPrimerCero(arr,mid+1,fin);
    }else {
        return buscarPrimerCero(arr,inicio,mid);
    }
}

int contarCeros(int *arr, int n) {
    if (arr[n-1] == 1) return 0;
    return n - buscarPrimerCero(arr,0,n-1);
}
