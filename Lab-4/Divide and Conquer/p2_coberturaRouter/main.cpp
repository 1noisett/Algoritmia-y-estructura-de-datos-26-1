#include <iostream>
using namespace std;

#define MAX_FIL 6
#define MAX_COL 9

int encontrarPico(int *arr,int inicio,int fin) {
    if (inicio==fin) return inicio;
    int medio = inicio + (fin-inicio)/2;

    if (arr[medio]==arr[medio+1]) {
        if (medio+2<=fin && arr[medio+1]<arr[medio+2]) {
            return encontrarPico(arr,medio+1,fin);
        }else {
            return encontrarPico(arr,inicio,medio);
        }
    }
    if (arr[medio]<arr[medio+1]) {
        return encontrarPico(arr,medio+1,fin);
    }else {
        return encontrarPico(arr,inicio,medio);
    }
}

int encontrarFila(int matriz[][MAX_COL],int inicio,int fin,int col) {
    if (inicio==fin) return inicio;
    int medio = inicio + (fin-inicio)/2;

    if (matriz[medio][col]<matriz[medio+1][col]) {
        return encontrarFila(matriz,medio+1,fin,col);
    }else {
        return encontrarFila(matriz,inicio,medio,col);
    }
}

int main() {
    int senal[MAX_FIL][MAX_COL] = {
        {10, 20, 20, 35, 50, 48, 30, 15,  5},
        {12, 25, 40, 70, 70, 60, 44, 22,  8},
        {15, 33, 55, 80, 95, 95, 60, 30, 10},
        {20, 40, 66, 66, 90, 99, 70, 40, 18},
        { 8, 16, 30, 52, 74, 60, 40, 20,  6},
        { 5, 14, 28, 44, 44, 38, 30, 18,  9}
    };
    int maximoGlobal = 0;
    int indMaximoLocal = -1;
    int indMaximoGlobal = -1;
    for (int i = 0; i < MAX_FIL; ++i) {
        indMaximoLocal = encontrarPico(senal[i],0,MAX_COL-1);
        int maximoLocal = senal[i][indMaximoLocal];
        if (maximoLocal>maximoGlobal) {
            maximoGlobal = maximoLocal;
            indMaximoGlobal = indMaximoLocal;
        }
    }
    cout<<indMaximoGlobal<<"  "<<maximoGlobal<<endl;
    cout<<encontrarFila(senal,0,MAX_FIL-1,indMaximoGlobal)<<endl;

    return 0;
}