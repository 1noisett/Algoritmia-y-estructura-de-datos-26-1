#include <iostream>
using namespace std;

int contar(int *arr,int inicio,int fin,int num) {
    if (inicio==fin) return arr[inicio]==num ? 1 :0;
    int medio = inicio + (fin-inicio)/2;
    int izq = contar(arr,inicio,medio,num);
    int der = contar(arr,medio+1,fin,num);
    return izq+der;
}

int elementoRepetido(int *arr,int inicio,int fin) {
    if (inicio==fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;

    if (medio%2==0) {
        if (arr[medio]==arr[medio+1]) return elementoRepetido(arr,medio+2,fin);
        else return elementoRepetido(arr,inicio,medio);
    }else {
        if (arr[medio]==arr[medio-1]) return elementoRepetido(arr,medio+1,fin);
        else return elementoRepetido(arr,inicio,medio-1);
    }
}

void merge(int *arr,int inicio,int medio,int fin) {
    int temp[fin-inicio+1];

    int i = inicio;
    int j = medio +1;
    int k = 0;
    while (i<=medio && j<=fin) {
        if (arr[i]<arr[j]) {
            temp[k] = arr[i]; i++;
        }else {
            temp[k] = arr[j]; j++;
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

void mergeSort(int *arr,int inicio,int fin) {
    if (inicio==fin) return;
    int medio = inicio + (fin-inicio)/2;

    mergeSort(arr,inicio,medio);
    mergeSort(arr,medio+1,fin);
    merge(arr,inicio,medio,fin);
}

#define N 10

int encontrarPrimerPos(int *arr,int inicio,int fin) {
    if (inicio==fin) return inicio;
    int medio = inicio + (fin-inicio)/2;

    if (arr[medio]>0) {
        return encontrarPrimerPos(arr,inicio,medio);
    }else {
        return encontrarPrimerPos(arr,medio+1,fin);
    }
}

int encontrarUltimoPos(int *arr,int inicio,int fin) {
    if (inicio==fin) return inicio-1;
    int medio = inicio + (fin-inicio)/2;

    if (arr[medio]>0) {
        return encontrarUltimoPos(arr,medio+1,fin);
    }else {
        return encontrarUltimoPos(arr,inicio,medio);
    }
}

int encontrarMaximo(int *arr,int inicio,int fin) {
    if (inicio==fin) return inicio;
    int medio = inicio + (fin-inicio)/2;

    if (arr[medio]==arr[medio+1]) {
        if (medio+2<=fin && arr[medio+1]<arr[medio+2]) {
            return encontrarMaximo(arr,medio+1,fin);
        }else {
            return encontrarMaximo(arr,inicio,medio);
        }
    }
    if (arr[medio]<arr[medio+1]) {
        return encontrarMaximo(arr,medio+1,fin);
    }else {
        return encontrarMaximo(arr,inicio,medio);
    }
}

int main() {
    // int arr[] = {1,6,3,4,5,6,3,7,5,4,3,1,7};
    // int n = sizeof(arr)/sizeof(arr[0]);
    // mergeSort(arr,0,n-1);
    // cout<<elementoRepetido(arr,0,n-1)<<endl;
    // cout<<contar(arr,0,n-1,3)<<endl;

    int matriz[N][N] = {
        {0, 0, 0, 3, 3, 7, 5, 5, 1, 1},
        {8, 8, 10, 9, 9, 5, 4, 4, 2, 0},
        {3, 5, 8, 9, 7, 6, 4, 2, 0, 0},
        {9, 7, 7, 4, 4, 4, 2, 0, 0, 0},
        {0, 2, 2, 3, 3, 4, 4, 5, 3, 3},
        {0, 0, 0, 0, 0, 0, 2, 3, 4, 5},
        {1, 2, 2, 3, 3, 4, 3, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 3, 5, 5, 7},
        {6, 5, 5, 2, 2, 1, 0, 0, 0, 0},
        {3, 2, 2, 0, 0, 0, 0, 0, 0, 0}
    };
    int maxMineral = 0;
    int fila;
    int col;
    int cantEstratos = 0;
    for (int i = 0; i < N; ++i) {
        int indMinLocal;
        int cantEstratosLocal = 0;
        if (matriz[i][0]==0) {
            int inicioArr = encontrarPrimerPos(matriz[i],0,N-1);
            indMinLocal = encontrarMaximo(matriz[i],inicioArr,N-1);
            cantEstratosLocal = N - inicioArr;
        }else {
            int finArr = encontrarUltimoPos(matriz[i],0,N-1);
            indMinLocal = encontrarMaximo(matriz[i],0,finArr);
            cantEstratosLocal = finArr+1;
        }
        int minLocal = matriz[i][indMinLocal];
        if (minLocal>maxMineral) {
            maxMineral = minLocal;
            fila = i;
            col = indMinLocal;
        }
        if (cantEstratosLocal>cantEstratos) cantEstratos = cantEstratosLocal;
    }
    cout<<maxMineral<<" encontrado en la muestra "<<fila+1<<", en el estrado "<<col+1<<endl<<endl;
    cout<<"mayor cantidad niveles con minerales: "<< cantEstratos<<" en las muestras: ";
    for (int i = 0; i < N; ++i) {
        int cantEstratosLocal;
        if (matriz[i][0]==0) {
            int inicioArr = encontrarPrimerPos(matriz[i],0,N-1);
            cantEstratosLocal = N - inicioArr;
        }else {
            int finArr = encontrarUltimoPos(matriz[i],0,N-1);
            cantEstratosLocal = finArr+1;
        }
        if (cantEstratosLocal==cantEstratos) cout<<i+1<<" ";
    }
    cout<<endl;


    return 0;
}
