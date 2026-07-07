#include <iostream>
using namespace std;

struct Producto {
    int numLote;
    int cantidad;
};

int encontrarPrimerIndice(Producto *arr,int inicio,int fin,int cantidad) {
    if (inicio==fin) {
        if (arr[inicio].cantidad==cantidad) return inicio;
        else return -1;
    }
    int medio = inicio + (fin-inicio)/2;
    if (arr[medio].cantidad<cantidad) {
        return encontrarPrimerIndice(arr,medio+1,fin,cantidad);
    }else {
        return encontrarPrimerIndice(arr,inicio,medio,cantidad);
    }
}

int encontrarUltimoIndice(Producto *arr,int inicio,int fin,int cantidad) {
    if (inicio==fin) {
        if (arr[inicio].cantidad==cantidad) return inicio;
        else return -1;
    }
    int medio = inicio + (fin-inicio)/2;
    if (arr[medio].cantidad==cantidad) {
        if (arr[medio].cantidad==arr[medio+1].cantidad) {
            return encontrarUltimoIndice(arr,medio+1,fin,cantidad);
        }else {
            return medio;
        }
    }else if (arr[medio].cantidad<cantidad){
        return encontrarUltimoIndice(arr,medio+1,fin,cantidad);
    }else {
        return encontrarUltimoIndice(arr,inicio,medio,cantidad);
    }
}


int main() {
    Producto productos[] = {
        {15872, 3},
        {15865, 4},
        {15866, 4},
        {14357, 6},
        {14365, 6},
        {14368, 6},
        {14370, 6},
        {19258, 8},
        {19260, 8}
    };
    int n = sizeof(productos)/sizeof(productos[0]);
    int cantidad = 8;
    int posicionInicial = encontrarPrimerIndice(productos,0,n-1,cantidad);
    int posicionFinal = encontrarUltimoIndice(productos,0,n-1,cantidad);

    cout<<"Para encontrar los lotes de "<<cantidad<<" productos:"<<endl;
    cout<<"Lote Inicial: "<<productos[posicionInicial].numLote<<endl;
    cout<<"Lote final: "<<productos[posicionFinal].numLote<<endl;
    return 0;
}
