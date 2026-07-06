#include <iostream>
using namespace std;

#define N 9

int encontrarCaries(int *arr,int inicio,int fin,int umbral,int &densidad) {
    if (inicio==fin) {
        if (arr[inicio]<umbral) {
            densidad = arr[inicio];
            return inicio;
        }else {
            densidad = -1;
            return -1;
        }
    }
    int medio = inicio + (fin-inicio)/2;
    if (arr[medio]<umbral) {
        return encontrarCaries(arr,inicio,medio,umbral,densidad);
    }else {
        return encontrarCaries(arr,medio+1,fin,umbral,densidad);
    }
}

void merge(int matriz[][N],int inicio,int medio,int fin) {
    int temp[N][N];
    int i = inicio;
    int j = medio+1;
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
        i++;
        k++;
    }
    while (j<=fin) {
        temp[0][k] = matriz[0][j];
        temp[1][k] = matriz[1][j];
        j++;
        k++;
    }
    for (int x = 0; x < k; ++x) {
        matriz[0][inicio+x] = temp[0][x];
        matriz[1][inicio+x] = temp[1][x];
    }
}

void mergeSort(int matriz[][N],int inicio,int fin) {
    if (inicio==fin) return;
    int medio = inicio + (fin-inicio)/2;
    mergeSort(matriz,inicio,medio);
    mergeSort(matriz,medio+1,fin);
    merge(matriz,inicio,medio,fin);
}

int encontrarMenor(int *arr,int inicio,int fin) {
    if (inicio==fin) return inicio;
    int medio = inicio + (fin-inicio)/2;

    if (arr[medio]<arr[fin]) {
        return encontrarMenor(arr,inicio,medio);
    }else {
        return encontrarMenor(arr,medio+1,fin);
    }
}

int max(int a,int b,int c) {
    int m = a > b ? a : b ;
    return m > c ? m : c;
}

int maxSumCruce(int *arr,int inicio,int medio,int fin) {
    int maxIzq = arr[medio];
    int sumaIzq = 0;
    for (int i = medio; i >= inicio; --i) {
        sumaIzq += arr[i];
        if (sumaIzq>maxIzq) maxIzq = sumaIzq;
    }
    int maxDer = arr[medio+1];
    int sumaDer = 0;
    for (int j = medio+1; j <= fin; ++j) {
        sumaDer += arr[j];
        if (sumaDer>maxDer) maxDer = sumaDer;
    }
    return maxIzq+maxDer;
}

int maxSumArray(int *arr,int inicio,int fin) {
    if (inicio==fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;

    int maxIzq = maxSumArray(arr,inicio,medio);
    int maxDer = maxSumArray(arr,medio+1,fin);
    int maxCruce =  maxSumCruce(arr,inicio,medio,fin);

    return max(maxIzq,maxDer,maxCruce);
}

int main() {
    // EJERCICIO DE CARIES
    // int arr[] = {98,95,93,90,72,60,55,50};
    // int n = sizeof(arr)/sizeof(arr[0]);
    // int densidad,umbral;
    // cout<<"Ingrese umbral(T): "; cin>>umbral;
    // int posicion = encontrarCaries(arr,0,n-1,umbral,densidad);
    // if (posicion==-1) {
    //     cout<<"No se detecta caries clínica."<<endl;
    // }else {
    //     cout<<"Primera zona con caries clínica detectada en la posición "<<posicion<<endl;
    //     cout<<"Densidad registrada: "<<densidad<<endl;
    // }

    // EJERCICIO DE CIBERSEGURIDAD
    int matriz[2][N] = {
        {80,90,10,20,30,40,50,60,70},
        {-4,-2,1,-3,6,-8,5,2,-1}
    };
    cout<<"Posición inicial original: "<<encontrarMenor(matriz[0],0,N-1)<<endl;
    mergeSort(matriz,0,N-1);


    cout<<"Máxima acumulación de riesgo en un intervalo continuo: "<<maxSumArray(matriz[1],0,N-1)<<endl;




    return 0;
}
