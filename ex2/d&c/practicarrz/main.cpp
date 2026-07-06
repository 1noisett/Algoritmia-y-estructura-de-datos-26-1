#include <iostream>
using namespace std;

#define N 30

int max(int a,int b,int c) {
    int m = a > b ? a : b;
    return m > c ? m : c;
}

int maxSumCruce(int *arr,int inicio,int medio,int fin) {
    int maxIzq = arr[medio];
    int sumaIzq = 0;
    for (int i = medio; i>=inicio; --i) {
        sumaIzq += arr[i];
        if (sumaIzq>maxIzq) maxIzq = sumaIzq;
    }
    int maxDer = arr[medio+1];
    int sumaDer = 0;
    for (int i = medio+1; i <= fin; ++i) {
        sumaDer += arr[i];
        if (sumaDer>maxDer) maxDer = sumaDer;
    }
    return maxIzq + maxDer;
}

int maxSumSubArray(int *arr,int inicio,int fin) {
    if (inicio==fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;

    int maxIzq = maxSumSubArray(arr,inicio,medio);
    int maxDer = maxSumSubArray(arr,medio+1,fin);
    int maxCruce = maxSumCruce(arr,inicio,medio,fin);

    return max(maxIzq,maxDer,maxCruce);
}

int merge(int *arr,int inicio,int medio,int fin) {
    int temp[N];
    int i = inicio;
    int j = medio + 1;
    int k = 0;
    int inversiones = 0;
    while (i<=medio && j<=fin) {
        if (arr[i]<=arr[j]) {
            temp[k] = arr[i]; i++;
        }else {
            temp[k] = arr[j]; j++;
            inversiones += medio - i + 1;
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
    return inversiones;
}

int mergeSort(int *arr,int inicio,int fin) {
    if (inicio==fin) return 0;
    int medio = inicio + (fin-inicio)/2;
    int invers = 0;

    invers += mergeSort(arr,inicio,medio);
    invers += mergeSort(arr,medio+1,fin);
    invers += merge(arr,inicio,medio,fin);

    return invers;
}

int encontrarUnicoElemento(int *arr,int inicio,int fin) {
    if (inicio==fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;

    if (medio%2==0) {
        if (arr[medio]==arr[medio+1]) {
            return encontrarUnicoElemento(arr,medio+2,fin);
        }else {
            return encontrarUnicoElemento(arr,inicio,medio);
        }
    }else {
        if (arr[medio]==arr[medio-1]) {
            return encontrarUnicoElemento(arr,medio+1,fin);
        }else {
            return encontrarUnicoElemento(arr,inicio,medio-1);
        }
    }
}

int encontrarPrimerCero(int *arr,int inicio,int fin) {
    if (inicio==fin) return inicio;
    int medio = inicio + (fin-inicio)/2;

    if (arr[medio]==0) {
        return encontrarPrimerCero(arr,inicio,medio);
    }else {
        return encontrarPrimerCero(arr,medio+1,fin);
    }
}

int contarCeros(int *arr,int n) {
    if (arr[n-1]==1) return 0;
    return n - encontrarPrimerCero(arr,0,n-1);
}

int encontrarMinimoArrRotado(int *arr,int inicio,int fin) {
    if (inicio==fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;

    if (arr[medio]>arr[fin]) {
        return encontrarMinimoArrRotado(arr,medio+1,fin);
    }else {
        return encontrarMinimoArrRotado(arr,inicio,medio);
    }
}

int encontrarMaximoArr(int *arr,int inicio,int fin) {
    if (inicio==fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;

    if (arr[medio]<arr[medio+1]) {
        return encontrarMaximoArr(arr,medio+1,fin);
    }else {
        return encontrarMaximoArr(arr,inicio,medio);
    }
}

int main() {
    int arr[] = {2, 4, 1, 3, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout<<mergeSort(arr,0,n-1)<<endl;
    return 0;
}
