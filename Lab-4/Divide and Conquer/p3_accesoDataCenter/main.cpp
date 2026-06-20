#include <iostream>
using namespace std;

#define N 8

void merge(int *arr,int inicio,int medio,int fin) {
    int temp[N];
    int i = inicio;
    int j = medio+1;
    int k = 0;
    while (i<=medio && j<=fin) {
        if (arr[i]<arr[j]) {
            temp[k] = arr[i];
            i++;
        } else {
            temp[k] = arr[j];
            j++;
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

int encontrarUnicoElemento(int *arr,int inicio,int fin,int inicioZona) {
    if (inicio==fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;

    if ((medio-inicioZona)%2==0) {
        if (arr[medio]==arr[medio+1]) {
            return encontrarUnicoElemento(arr,medio+2,fin,inicioZona);
        }else {
            return encontrarUnicoElemento(arr,inicio,medio,inicioZona);
        }
    }else {
        if (arr[medio]==arr[medio-1]) {
            return encontrarUnicoElemento(arr,medio+1,fin,inicioZona);
        }else {
            return encontrarUnicoElemento(arr,inicio,medio-1,inicioZona);
        }
    }
}

int encontrarIndicePrimerPositivo(int *arr,int inicio,int fin) {
    if (inicio==fin) {
        if (arr[inicio]>0) return inicio;
        else return 0;
    }
    int medio = inicio + (fin-inicio)/2;
    if (arr[medio]>0) {
        return encontrarIndicePrimerPositivo(arr,inicio,medio);
    }else {
        return encontrarIndicePrimerPositivo(arr,medio+1,fin);
    }
}

int main() {
    int registros[N][N] = {
        {0, 0, 5, 5, 9, 2, 2, 9},
        {0, 7, 3, 7, 4, 3, 4, 1},
        {6, 6, 8, 2, 8, 2, 9, 9},
        {0, 0, 0, 4, 4, 7, 9, 7},
        {3, 1, 3, 1, 5, 8, 8, 5},
        {0, 2, 5, 2, 5, 6, 7, 6},
        {4, 4, 0, 0, 0, 0, 1, 1},
        {0, 0, 9, 3, 9, 3, 6, 6}
    };
    for (int i = 0; i < N; ++i) {
        mergeSort(registros[i],0,N-1);
        int primerIndPos = encontrarIndicePrimerPositivo(registros[i],0,N-1);
        int cantidadNums = N - primerIndPos;
        if (cantidadNums%2==0) {
            cout<<"Todos en parejas"<<endl;
        }else {
            cout<<encontrarUnicoElemento(registros[i],primerIndPos,N-1,primerIndPos)<<endl;
        }
    }
    return 0;
}
