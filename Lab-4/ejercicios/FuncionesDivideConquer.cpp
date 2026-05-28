//
// Created by Miguel on 5/25/2026.
//

#include "FuncionesDivideConquer.h"

// int elemSoloUnaVez(int *arr,int n) {
//     int low = 0;
//     int high = n-1;
//
//     while (low<high) {
//         int mid = low + (high-low)/2;
//         // forzamos que 'mid' sea par para evaluar el inicio del par
//         if (mid % 2 == 1) mid--;
//         // si el elemento en mid es igual al siguiente, el patrón esta intacto
//         if (arr[mid] == arr[mid+1]) {
//             low = mid + 2;
//         }else {
//             high = mid;
//         }
//     }
//     return arr[low];
// }


/*
* Antes del único: las parejas empiezan en índice par.
* Después del único: las parejas empiezan en índice impar.
*/
int encontrarUnico(int *arr, int inicio, int fin) {
    // caso base: solo queda un elemento
    if (inicio == fin) return arr[inicio];

    int mid = inicio + (fin-inicio)/2;

    if (mid % 2 == 0) {
        // mid es par -> comparamos con el siguiente
        if (arr[mid] == arr[mid+1]) {
            // pareja bien formada -> el único está a la derecha
            return encontrarUnico(arr,mid+2,fin);
        }else {
            // pareja rota -> el único está a la izquierda
            return encontrarUnico(arr,inicio,mid);
        }
    }else {
        // mid es impar -> comparamos con el anterior
        if (arr[mid] == arr[mid-1]) {
            // pareja bien formada -> el único está a la derecha
            return encontrarUnico(arr,mid+1,fin);
        }else {
            // pareja rota -> el único está a la izquierda
            return encontrarUnico(arr,inicio,mid);
        }
    }
}

int buscarPrimerCero(int *arr, int inicio, int fin) {
    if (inicio == fin) return inicio;

    int mid = inicio + (fin-inicio)/2;
    if (arr[mid] == 1) {
        // descartamos la parte izquierda
        return buscarPrimerCero(arr,mid+1,fin);
    }else{
        // mid == 0 -> estamos al inicio del arreglo, en caso no, evaluamos si el anterior es -1
        if (mid == 0 || arr[mid-1] == 1) {
            return mid;
        }else {
            //descartamos la parte derecha
            return buscarPrimerCero(arr,inicio,mid-1);
        }
    }
}

int contarCeros(int *arr, int n) {
    if (n==0 || arr[n-1] == 1) return 0;
    return n - buscarPrimerCero(arr,0,n-1);
}

int encontrarMinimo(int *arr,int inicio,int fin) {
    // caso base
    if (inicio==fin) return arr[inicio];
    if (arr[fin] > arr[inicio]) return arr[inicio];

    int mid = inicio + (fin - inicio)/2;
    if (mid > 0 && arr[mid] < arr[mid-1]) {
        return arr[mid];
    }else {
        if (arr[mid] < arr[fin]) {
            return encontrarMinimo(arr,inicio,mid-1);
        }else {
            return encontrarMinimo(arr,mid+1,fin);
        }
    }
}



















