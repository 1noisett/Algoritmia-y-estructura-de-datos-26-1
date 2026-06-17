#include <iostream>
using namespace std;

#define MAX_FIL 2
#define MAX_COL 10

int encontrarElemRotado(int *arr,int inicio,int fin,int &indice) {
    if (inicio==fin) {
        indice = inicio;
        return arr[inicio];
    }
    int medio = inicio + (fin-inicio)/2;

    if (arr[medio]<arr[fin]) {
        return encontrarElemRotado(arr,inicio,medio,indice);
    }else {
        return encontrarElemRotado(arr,medio+1,fin,indice);
    }
}

void merge(int matriz[][MAX_COL],int inicio,int medio,int fin) {

    int temp[MAX_FIL][MAX_COL];

    int i = inicio;
    int j = medio + 1;
    int k = 0;
    while (i<=medio && j<=fin) {
        if (matriz[0][i]<matriz[0][j]) {
            temp[0][k] = matriz[0][i];
            temp[1][k] = matriz[1][i];
            i++;
        }else {
            temp[0][k] = matriz[0][j];
            temp[1][k] = matriz[1][j];
            j++;
        }
        k++;
    }
    while (i<=medio) {
        temp[0][k] = matriz[0][i];
        temp[1][k] = matriz[1][i];
        i++; k++;
    }
    while (j<=fin) {
        temp[0][k] = matriz[0][j];
        temp[1][k] = matriz[1][j];
        j++; k++;
    }
    for (int x = 0; x < k; ++x) {
        matriz[0][inicio+x] = temp[0][x];
        matriz[1][inicio+x] = temp[1][x];
    }
}

void mergeSort(int matriz[][MAX_COL],int inicio,int fin) {
    if (inicio==fin) return;
    int medio = inicio + (fin-inicio)/2;

    mergeSort(matriz,inicio,medio);
    mergeSort(matriz,medio+1,fin);
    merge(matriz,inicio,medio,fin);
}

int maxSumArrCruce(int *arr,int inicio,int medio,int fin) {
    int maxIzq = arr[medio];
    int sumaIzq = 0;
    for (int i = medio; i >= inicio; --i) {
        sumaIzq += arr[i];
        if (sumaIzq>maxIzq) maxIzq = sumaIzq;
    }

    int maxDer = arr[medio+1];
    int sumaDer = 0;
    for (int i = medio+1; i <= fin; ++i) {
        sumaDer += arr[i];
        if (sumaDer>maxDer) maxDer = sumaDer;
    }
    return maxIzq+maxDer;
}

int max3(int a,int b,int c) {
    int m = a > b ? a : b;
    return m>c ? m:c;
}

int maxSumArray(int *arr,int inicio,int fin) {
    if (inicio==fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;

    int maxixq = maxSumArray(arr,inicio,medio);
    int maxDer = maxSumArray(arr,medio+1,fin);
    int maxCruce = maxSumArrCruce(arr,inicio,medio,fin);

    return max3(maxixq,maxDer,maxCruce);
}

int main() {
    int matriz[MAX_FIL][MAX_COL] = {
        {40, 50, 60, 70, 80, 90, 100, 10, 20, 30},
        { 6, -4, -9,  0,  7, -1,   4, -3,  1,  4}
    };
    int indiceRotado;
    encontrarElemRotado(matriz[0],0,MAX_COL-1,indiceRotado);
    cout<<"Posición inicial: "<<indiceRotado<<endl;
    mergeSort(matriz,0,MAX_COL-1);
    cout<<"Máxima acumulación de riesgo en un intervalo continuo: "<<maxSumArray(matriz[1],0,MAX_COL-1)<<endl;
    return 0;
}
