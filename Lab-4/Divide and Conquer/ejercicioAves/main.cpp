#include <iostream>
using namespace std;

#define N 6

void merge(int *arr,int inicio,int medio,int fin) {
    int n = fin-inicio+1;
    int temp[n];

    int i = inicio;
    int j = medio+1;
    int k = 0;
    while (i<=medio && j<=fin) {
        if (arr[i]>arr[j]) {
            temp[k] = arr[j];
            j++;
        }else {
            temp[k] = arr[i];
            i++;
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
    int medio = (inicio+fin)/2;
    mergeSort(arr,inicio,medio);
    mergeSort(arr,medio+1,fin);
    merge(arr,inicio,medio,fin);
}

int encontrarPrimerPositivo(int *arr,int inicio,int fin) {
    if (inicio==fin) return inicio;
    int medio = inicio + (fin-inicio)/2;

    if (arr[medio]>0) {
        return encontrarPrimerPositivo(arr,inicio,medio);
    }else {
        return encontrarPrimerPositivo(arr,medio+1,fin);
    }
}

int encontrarUnicoElemento(int *arr,int inicio,int fin,int inicioZona) {
    if (inicio==fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;

    if ((medio-inicioZona)%2==0) {
        if (arr[medio] == arr[medio+1]) {
            return encontrarUnicoElemento(arr,medio+2,fin,inicioZona);
        }else {
            return encontrarUnicoElemento(arr,inicio,medio,inicioZona);
        }
    }else {
        if (arr[medio] == arr[medio-1]) {
            return encontrarUnicoElemento(arr,medio+1,fin,inicioZona);
        }else {
            return encontrarUnicoElemento(arr,inicio,medio,inicioZona);
        }
    }
}

/*
 * Por fila, a lo más una mutacion queda sin pareja (falta a lo más un ave).
 * Esto da exactamente dos casos:
 *   - 0 faltantes: todas las mutaciones en parejas -> cantidad par -> "Sin faltante"
 *   - 1 faltante: una mutacion queda con un solo ejemplar -> cantidad impar
 * La garantia "a lo más uno" asegura una sola transicion de paridad,
 * que es lo que hace válida la busqueda binaria (cerrar rango).
 */

int main() {

    int matriz[N][N] = {
        {0, 3, 7, 2, 2, 7},
        {5, 0, 3, 1, 5, 3},
        {7, 7, 3, 6, 6, 3},
        {7, 4, 0, 7, 2, 4},
        {5, 1, 2, 5, 1, 2},
        {6, 0, 7, 4, 7, 4}
    };


    for (int i = 0; i < N; ++i) {
        mergeSort(matriz[i],0,N-1);
        int inicioZona = encontrarPrimerPositivo(matriz[i],0,N-1);

        int cantidadAves = N - inicioZona;
        if (cantidadAves%2==0) {
            cout<<"Sin faltante";
        }else {
            cout<<encontrarUnicoElemento(matriz[i],inicioZona,N-1,inicioZona);
        }
        cout << endl;
    }


    return 0;
}
