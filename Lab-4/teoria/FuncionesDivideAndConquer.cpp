//
// Created by Miguel on 5/24/2026.
//

#include "FuncionesDivideAndConquer.h"
#include <iostream>


int binarySearch(int *array,int n,int num) {
    int inicio = 0;
    int fin = n-1;

    while (inicio <= fin) {
        int medio = (inicio + fin)/2;
        if (array[medio] == num) {
            return medio;
        }else if (array[medio] < num) {
            inicio = medio + 1;
        }else {
            fin = medio - 1;
        }
    }
    return -1;
}

void mergeSort(int *arreglo,int inicio, int fin) {
    // caso base
    if (inicio==fin) return;
    // parte recursiva
    int medio = (inicio + fin)/2;
    mergeSort(arreglo,inicio,medio); // izq arreglo
    mergeSort(arreglo,medio+1,fin); // der arreglo
    merge(arreglo,inicio,medio,fin); // fusionar
}

void merge(int *arreglo, int inicio, int medio, int fin) {
    // complejidad O(n) en tiempo y O(n) en espacio adicional
    // inicio, medio y fin son índices, size es el tamano
    int size = fin - inicio + 1;
    int temp[size];
    for (int i = 0; i < size; ++i) {
        temp[i] = arreglo[inicio + i];
    }
    int izquierda = 0;
    int derecha = medio - inicio + 1;
    // medio - inicio -> último índice válido de la mitad izquierda
    // fin - inicio -> último índice válido de la mitad derecha
    for (int indice = 0; indice < size; ++indice) {
        if (derecha <= fin - inicio)          // quedan elementos en la mitad derecha?
            if (izquierda <= medio - inicio)  // quedan elementos en la mitad izquierda?
                if (temp[izquierda] > temp[derecha])
                    arreglo[inicio+indice] = temp[derecha++];   // gana derecha (es menor)
                else
                    arreglo[inicio+indice] = temp[izquierda++]; // gana izquierda(<=)
            else
                arreglo[inicio+indice] = temp[derecha++]; // izq agotada -> drena der
        else                                              // der agotada -> drena izq
            arreglo[inicio+indice] = temp[izquierda++];
    }
}



void imprimeArreglo(int arreglo[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arreglo[i] << ", ";
    }
}