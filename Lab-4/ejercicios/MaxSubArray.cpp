//
// Created by Miguel Bazan on 2/06/26.
//

#include "MaxSubArray.h"

int max3(int a, int b, int c) {
    int m = a > b ? a : b;
    return m > c ? m : c;
}

int maxMidSubArray(int *arr, int inicio, int medio, int fin) {
    // bucle 1: desde medio hacia la izquierda
    int sumaIzq = 0;
    int mejorIzq = arr[medio];
    for (int i = medio; i >= inicio; --i) {
        sumaIzq += arr[i];
        if (sumaIzq > mejorIzq) mejorIzq = sumaIzq;
    }

    // bucle 2: desde medio hacia la derecha
    int sumaDer = 0;
    int mejorDer = arr[medio+1];
    for (int i = medio + 1; i <= fin; ++i) {
        sumaDer += arr[i];
        if (sumaDer>mejorDer) mejorDer = sumaDer;
    }

    // el mejor cruce es la mejor mitad izquierda + la mejor mitad derecha
    return mejorIzq + mejorDer;
}

int maxSubArray(int *arr, int inicio, int fin) {
    // caso base: un solo elemento
    if (inicio == fin) return arr[inicio];

    // dividir: encuentro el punto medio
    int medio = inicio + (fin-inicio)/2;

    // vencer: resuelvo cada mitad por recursión
    int maxIzq = maxSubArray(arr,inicio,medio);            // todo en la izq
    int maxDer = maxSubArray(arr,medio+1,fin);           // todo en la der
    int maxCruce = maxMidSubArray(arr,inicio,medio,fin);      // cruzando el medio

    // combinar: la respuesta es el máximo de los tres casos
    return max3(maxIzq,maxDer,maxCruce);
}
