#include <iostream>
using namespace std;

int primerPositivo(int *arr,int inicio,int fin) {
    if (inicio==fin) return inicio;

    int medio = inicio + (fin - inicio)/2;

    if (arr[medio] > 0) {
        // cuando arr[medio] > 0, medio también es candidato
        return primerPositivo(arr,inicio,medio);
    }else {
        // la parte izquierda queda descartada inccluido medio
        return primerPositivo(arr,medio+1,fin);
    }
}
/*
* casillero real:   5   6   7   8   9  10  ...
* mi cuenta nueva:  0   1   2   3   4   5  ...
 */
int buscarUnicoElemento(int *arr,int inicio,int fin, int inicioZona) {
    if (inicio==fin) return arr[inicio];

    int medio = inicio + (fin - inicio)/2;

    if ((medio-inicioZona) % 2 == 0) {
        if (arr[medio] == arr[medio+1]) {
            return buscarUnicoElemento(arr,medio+2,fin,inicioZona);
        }else {
            return buscarUnicoElemento(arr,inicio,medio,inicioZona);
        }
    }else {
        if (arr[medio] == arr[medio-1]) {
            return buscarUnicoElemento(arr,medio+1,fin,inicioZona);
        }else {
            return buscarUnicoElemento(arr,inicio,medio,inicioZona);
        }
    }
}

int main() {
    // int arr[] = {-1, 0, -1, 0, 1, 1, 2, 2, 3, 3, 4, 3, 3, 2, 2, 1, 1};
    int arr[] = {0, -1, 0, -1, 0, 1, 1, 2, 2, 3, 2, 2, 1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    int indUltCero = primerPositivo(arr,0,n-1);
    int radiacionMaxima = buscarUnicoElemento(arr,indUltCero,n-1,indUltCero);
    cout<<"La radiación empieza a "<<indUltCero<<" km. Potencia máxima "<<radiacionMaxima<<" megatones"<<endl;
    return 0;
}
