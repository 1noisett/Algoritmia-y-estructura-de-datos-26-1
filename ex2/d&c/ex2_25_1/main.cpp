#include <iostream>
using namespace std;

int encontrarPosicionRotado(int *arr,int inicio,int fin) {
    if (inicio==fin) return inicio;
    int medio = inicio + (fin-inicio)/2;

    if (arr[medio]>arr[fin]) {
        return encontrarPosicionRotado(arr,medio+1,fin);
    }else {
        return encontrarPosicionRotado(arr,inicio,medio);
    }
}

int encontrarNumero(int *arr,int inicio,int fin,int codAlerta) {
    if (inicio==fin) {
        if (arr[inicio]==codAlerta)
            return inicio;
        else
            return -1;
    }
    int medio = inicio + (fin-inicio)/2;

    if (arr[medio]<codAlerta) {
        return encontrarNumero(arr,medio+1,fin,codAlerta);
    }else {
        return encontrarNumero(arr,inicio,medio,codAlerta);
    }
}

int merge(int *arr,int inicio,int medio,int fin) {
    int temp[fin-inicio+1];
    int inversiones = 0;

    int i = inicio;
    int j = medio+1;
    int k = 0;
    while (i<=medio && j<=fin) {
        if (arr[i]<arr[j]) {
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
    int invrs = 0;

    invrs += mergeSort(arr,inicio,medio);
    invrs += mergeSort(arr,medio+1,fin);
    invrs += merge(arr,inicio,medio,fin);
    return invrs;
}

int main() {
    // int arr[] = {300,350,400,450,500,550,600,650,100,145,190,235,280};
    // int n = sizeof(arr)/sizeof(arr[0]);
    // int codAlerta;
    // cout<<"Ingrese el código de alerta a buscar: "; cin>>codAlerta;
    // int posicionRotado = encontrarPosicionRotado(arr,0,n-1);
    // int posicionEncontrada;
    // if (codAlerta>arr[n-1]) {
    //     posicionEncontrada = encontrarNumero(arr,0,posicionRotado-1,codAlerta);
    //     if (posicionEncontrada==-1) cout<<"Codigo de alerta "<<codAlerta<<" no encontrado"<<endl;
    //     else cout<<"Código de alerta "<<codAlerta<<" encontrado en la posición "<<posicionEncontrada+1<<endl;
    // }else {
    //     posicionEncontrada = encontrarNumero(arr,posicionRotado,n-1,codAlerta);
    //     if (posicionEncontrada==-1) cout<<"Codigo de alerta "<<codAlerta<<" no encontrado"<<endl;
    //     else cout<<"Código de alerta "<<codAlerta<<" encontrado en la posición "<<posicionEncontrada+1<<endl;
    // }

    int arr[] = {10,12,14,13,11,15};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout<<mergeSort(arr,0,n-1)<<endl;

    return 0;
}
