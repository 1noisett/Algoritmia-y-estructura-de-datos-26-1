#include <iostream>
using namespace std;

int min3(int maxIzq,int maxDer,int cruce) {
    int m = maxIzq > maxDer ? maxDer : maxIzq;
    return m > cruce ? cruce : m;
}

int maxSumCruce(int *arr,int inicio,int medio,int fin) {
    int mejorIzq = arr[medio];
    int sumaIzq = 0;
    for (int i = medio; i >= inicio; --i) {
        sumaIzq += arr[i];
        if (sumaIzq < mejorIzq) mejorIzq = sumaIzq;
    }

    int mejorDer = arr[medio+1];
    int sumaDer = 0;
    for (int i = medio+1; i <= fin; ++i) {
        sumaDer += arr[i];
        if (sumaDer < mejorDer) mejorDer = sumaDer;
    }
    return mejorDer + mejorIzq;
}

int maxSumNegSubArr(int *arr,int inicio, int fin) {
    if (inicio == fin) return arr[inicio];

    int medio = inicio + (fin - inicio)/2;

    int minIzq = maxSumNegSubArr(arr, inicio, medio);
    int minDer = maxSumNegSubArr(arr, medio+1, fin);
    int cruce = maxSumCruce(arr,inicio,medio,fin);

    return min3(minIzq,minDer,cruce);
}


int main() {
    // int arr[] = {2, 5, -6, 2, 3, -1, -5, 6};
    // int arr[] = {2, -3, 4, -5, -7};
    int arr[] = {-4, 5, 6, -4, 3, -1, -5, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout<<maxSumNegSubArr(arr,0,n-1);
    return 0;
}
