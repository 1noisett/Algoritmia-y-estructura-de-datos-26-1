//
// Created by Miguel on 5/25/2026.
//

#include "FuncionesDivideConquer.h"

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

int encontrarMinimo(int *arr,int inicio,int fin) {
    // caso base
    if (inicio==fin) return arr[inicio];

    int medio = inicio + (fin - inicio)/2;

    if (arr[medio] > arr[fin]) {
        // hay una "caída" entre mid y fin → el mínimo está en esa caída → a la derecha de mid.
        return encontrarMinimo(arr,medio+1,fin);
    }else {
        // de mid a fin solo sube → el mínimo no está ahí → está a la izquierda (o es mid).
        return encontrarMinimo(arr,inicio,medio);
    }

}

int encontrarValorMax(int *arr, int inicio, int fin) {
    if (inicio == fin) return arr[inicio];

    int medio = inicio + (fin-inicio)/2;

    if (arr[medio] > arr[medio+1]) {
        return encontrarValorMax(arr,inicio,medio);
    }else {
        return encontrarValorMax(arr,medio+1,fin);
    }
}















