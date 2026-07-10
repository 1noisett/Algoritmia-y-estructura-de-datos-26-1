#include <iostream>
using namespace std;

int maxSumCruce(int *arr,int inicio,int medio,int fin) {
    int menorIzq = arr[medio];
    int sumaIzq = 0;
    for (int i = medio; i >= inicio; --i) {
        sumaIzq += arr[i];
        if (sumaIzq<menorIzq) menorIzq = sumaIzq;
    }
    int menorDer = arr[medio+1];
    int sumaDer = 0;
    for (int i = medio+1 ; i <= fin; ++i) {
        sumaDer += arr[i];
        if (sumaDer<menorDer) menorDer = sumaDer;
    }
    return menorIzq + menorDer;
}

int max3(int a,int b,int c) {
    int m = a > b? b:a;
    return m>c? c:m;
}

int maxSumArray(int *arr,int inicio,int fin) {
    if (inicio==fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;

    int maxIzq = maxSumArray(arr,inicio,medio);
    int maxDer = maxSumArray(arr,medio+1,fin);
    int maxCruce = maxSumCruce(arr,inicio,medio,fin);

    return max3(maxIzq,maxDer,maxCruce);
}

int encontrarPrimerPos(int *arr,int inicio,int fin) {
    if (inicio==fin) return inicio;
    int medio = inicio + (fin-inicio)/2;

    if (arr[medio]<=0) {
        return encontrarPrimerPos(arr,medio+1,fin);
    }else {
        return encontrarPrimerPos(arr,inicio,medio);
    }
}

int encontrarUnicoElem(int *arr,int inicio,int fin,int inicioZona) {
    if (inicio==fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;

    if ((medio-inicioZona)%2==0) {
        if (arr[medio]==arr[medio+1]) return encontrarUnicoElem(arr,medio+2,fin,inicioZona);
        else return encontrarUnicoElem(arr,inicio,medio,inicioZona);
    }else {
        if (arr[medio]==arr[medio-1]) return encontrarUnicoElem(arr,medio+1,fin,inicioZona);
        else return encontrarUnicoElem(arr,inicio,medio-1,inicioZona);
    }
}

int main() {
    // int arr[] = {2, 5, -6, 2, 3, -1, -5, 6};
    // int arr[] = {2, -3, 4, -5, -7};
    // int arr[] = {-4, 5, 6, -4, 3, -1, -5, 6};
    // int n = sizeof(arr)/sizeof(arr[0]);
    // cout<<maxSumArray(arr,0,n-1)<<endl;


    int arr[] = {-1,0,-1,0,1,1,2,2,3,3,4,3,3,2,2,1,1};
    int n = sizeof(arr)/sizeof(arr[0]);
    int potenciaMax = encontrarPrimerPos(arr,0,n-1);
    int megatones = encontrarUnicoElem(arr,potenciaMax,n-1,potenciaMax);
    cout<<"La radiación empieza a "<<potenciaMax<<"km."<<endl;
    cout<<"Potencia máxima a "<<megatones<<" megatones"<<endl;
    return 0;
}
