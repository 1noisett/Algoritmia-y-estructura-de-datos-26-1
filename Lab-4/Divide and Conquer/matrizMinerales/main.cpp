#include <iostream>
using namespace std;

#define N 10

int encontrarMaximoValor(int *arr,int inicio,int fin,int &columMax) {
    if (inicio == fin) {
        columMax = inicio; return arr[inicio];
    }
    int medio = inicio + (fin - inicio)/2;

    // caso: arr[medio] = arr[medio+1], el empate no dice el lado
    // evaluamos medio + 2 solo si es <= fin para no leer fuera del arreglo

    if (arr[medio] == arr[medio+1]) {
        if (medio+2<=fin && arr[medio+1] < arr[medio+2]) {
            return encontrarMaximoValor(arr,medio+1,fin,columMax);
        }else {
            return encontrarMaximoValor(arr,inicio,medio,columMax);
        }
    }

    // caso normal (sin igualdad)
    if (arr[medio] > arr[medio+1]) {
        return encontrarMaximoValor(arr,inicio,medio,columMax);
    }else {
        return encontrarMaximoValor(arr,medio+1,fin,columMax);
    }
}

int primerPositivo(int *arr,int inicio,int fin) {
    if (inicio == fin) return inicio;

    int medio = inicio + (fin - inicio)/2;
    if (arr[medio] > 0) {
        return primerPositivo(arr,inicio,medio);
    }else {
        return primerPositivo(arr,medio+1,fin);
    }
}

int obtenerPrimerCeroDer(int *arr,int inicio,int fin) {
    if (inicio == fin) return inicio;

    int medio = inicio + (fin - inicio)/2;
    if (arr[medio] == 0) {
        return obtenerPrimerCeroDer(arr,inicio,medio);
    }else {
        return obtenerPrimerCeroDer(arr,medio+1,fin);
    }
}

int contarMinerales(int *arr,int inicio,int fin) {

    if (arr[inicio]==0) {
        return N - primerPositivo(arr,inicio,fin);
    }else {
        return obtenerPrimerCeroDer(arr,inicio,fin);
    }
}

int main() {
    int matriz[N][N] = {
        {0,0,0,3,3,7,5,5,1,1},
        {8,8,10,9,9,5,4,4,2,0},
        {3,5,8,9,7,6,4,2,0,0},
        {9,7,7,4,4,4,2,0,0,0},
        {0,2,2,3,3,4,4,5,3,3},
        {0,0,0,0,0,0,2,3,4,5},
        {1,2,2,3,3,4,3,2,0,0},
        {0,0,0,0,0,0,3,5,5,7},
        {6,5,5,2,2,1,0,0,0,0},
        {3,2,2,0,0,0,0,0,0,0}
    };
    int mejorEstrato = -1, muestraMax = 0, estratoMax = 0;
    for (int i = 0; i < N; i++) {
        int col;
        int estratoFila = encontrarMaximoValor(matriz[i],0,N-1,col);
        if (estratoFila>mejorEstrato) {
            mejorEstrato = estratoFila;
            muestraMax = i;
            estratoMax = col;
        }
    }
    cout << "La maxima pureza de las muestras es: " << mejorEstrato << " (encontrado en la muestra "<<(muestraMax+1);
    cout << ", en el estrato "<<(estratoMax+1)<<")"<<endl<<endl;

    int maxMin = 0;
    for (int i = 0; i < N; i++) {
        int mineral = contarMinerales(matriz[i],0,N-1);
        if (mineral>maxMin) maxMin = mineral;
    }
    cout<<"Las muestras con mayor cantidad de niveles con minerales son: ";
    for (int i = 0; i < N; i++) {
        if (contarMinerales(matriz[i],0,N-1) == maxMin) {
            cout << i + 1 << ", ";
        }
    }
    cout<<"ambos con "<< maxMin<< " estratos de minerales."<<endl;
    return 0;
}
