#include <iostream>
#include "BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h"
using namespace std;

#define MAX_FIL 4
#define MAX_COL 7
#define N MAX_FIL*MAX_COL

struct Producto {
    int dia;
    int turno;
    int cantidad;
};

void mergeDiaTurno(Producto *arr,int inicio,int medio,int fin) {
    Producto temp[N];

    int i = inicio;
    int j = medio + 1;
    int k = 0;
    while (i<=medio && j<=fin) {
        if (arr[i].dia<arr[j].dia || (arr[i].dia == arr[j].dia && arr[i].turno < arr[j].turno)) {
            temp[k] = arr[i]; i++;
        }else {
            temp[k] = arr[j]; j++;
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

void mergeSortDiaTurno(Producto *arr,int inicio,int fin) {
    if (inicio==fin) return;
    int medio = inicio + (fin-inicio)/2;

    mergeSortDiaTurno(arr,inicio,medio);
    mergeSortDiaTurno(arr,medio+1,fin);
    mergeDiaTurno(arr,inicio,medio,fin);
}

void mergeCantidad(Producto *arr, int inicio, int medio, int fin) {
    Producto temp[N];
    int i = inicio;
    int j = medio + 1;
    int k = 0;

    while (i <= medio && j <= fin) {
        // arr[i] va antes que arr[j] si: menor cantidad, o igual cantidad y menor dia,
        // o iguales cantidad y dia y menor turno.
        bool izqVaPrimero =
            (arr[i].cantidad <  arr[j].cantidad) ||
            (arr[i].cantidad == arr[j].cantidad && arr[i].dia <  arr[j].dia) ||
            (arr[i].cantidad == arr[j].cantidad && arr[i].dia == arr[j].dia && arr[i].turno < arr[j].turno);

        if (izqVaPrimero) {
            temp[k] = arr[i]; i++;
        } else {
            temp[k] = arr[j]; j++;
        }
        k++;
    }
    while (i <= medio) { temp[k] = arr[i]; i++; k++; }
    while (j <= fin)   { temp[k] = arr[j]; j++; k++; }

    for (int x = 0; x < k; ++x) {
        arr[inicio + x] = temp[x];
    }
}

void mergeSortCantidad(Producto *arr,int inicio,int fin) {
    if (inicio==fin) return;
    int medio = inicio + (fin-inicio)/2;

    mergeSortCantidad(arr,inicio,medio);
    mergeSortCantidad(arr,medio+1,fin);
    mergeCantidad(arr,inicio,medio,fin);
}


void insertaDiaTurnoRecursivo(NodoArbolBinarioBusqueda *&nodo,Producto *arr,int inicio,int fin) {
    if (inicio>fin) return;
    int medio = inicio + (fin-inicio)/2;
    ElementoArbolBinarioBusqueda e = {arr[medio].dia,arr[medio].turno,arr[medio].cantidad};
    plantarNodoArbolBinario(nodo,nullptr,e,nullptr);
    insertaDiaTurnoRecursivo(nodo->izq,arr,inicio,medio-1);
    insertaDiaTurnoRecursivo(nodo->der,arr,medio+1,fin);
}

void insertaDiaTurno(ArbolBinarioBusqueda &arbol,Producto *arr,int inicio,int fin) {
    insertaDiaTurnoRecursivo(arbol.raiz,arr,inicio,fin);
}

void insertaCantidadRecursivo(NodoArbolBinarioBusqueda *&nodo,Producto *arr,int inicio,int fin) {
    if (inicio>fin) return;
    int medio = inicio + (fin-inicio)/2;
    ElementoArbolBinarioBusqueda e = {arr[medio].dia,arr[medio].turno,arr[medio].cantidad};
    plantarNodoArbolBinario(nodo,nullptr,e,nullptr);
    insertaCantidadRecursivo(nodo->izq,arr,inicio,medio-1);
    insertaCantidadRecursivo(nodo->der,arr,medio+1,fin);
}

void insertaCantidad(ArbolBinarioBusqueda &arbol,Producto *arr,int inicio,int fin) {
    insertaCantidadRecursivo(arbol.raiz,arr,inicio,fin);
}

int main() {
    int cantidades[MAX_FIL][MAX_COL] = {
        {100, 103, 100, 101, 100,  99, 100},  // turno 1
        {100, 102, 102,  92,  99, 100,  98},  // turno 2
        {100, 100, 102, 100, 100, 101, 100},  // turno 3
        { 98,  96,  93,  99, 100, 102,  95}   // turno 4
    };

    // aplano la matriz a un arreglo de 28 productos, el día y turno salen de la posición en la matriz
    Producto datos[N];
    int k = 0;
    for (int t = 0; t < MAX_FIL; ++t) {
        for (int d = 0; d < MAX_COL; ++d) {
            datos[k].turno = t+1;       // turno 1..4
            datos[k].dia = d+1;         // día 1..7
            datos[k].cantidad = cantidades[t][d];
            k++;
        }
    }
    ArbolBinarioBusqueda arbolDiaTurno;
    construir(arbolDiaTurno);
    mergeSortDiaTurno(datos,0,N-1);
    insertaDiaTurno(arbolDiaTurno,datos,0,N-1);

    cout<<"Arbol día y turno"<<endl;
    cout<<"recorrer en orden: "<<endl;
    recorrerInOrder(arbolDiaTurno);
    cout<<endl;
    if (esEquilibrado(arbolDiaTurno)) cout<<"Sí es equilibrado";
    else cout<<"No es equilibrado";

    cout<<endl<<endl;

    cout<<"Arbol cantidad"<<endl;
    ArbolBinarioBusqueda arbolCantidad;
    construir(arbolCantidad);
    mergeSortCantidad(datos,0,N-1);
    insertaCantidad(arbolCantidad,datos,0,N-1);

    cout<<"recorrer en orden: "<<endl;
    recorrerInOrder(arbolCantidad);
    cout<<endl;
    if (esEquilibrado(arbolCantidad)) cout<<"Sí es equilibrado";
    else cout<<"No es equilibrado";

    destruirArbolBinario(arbolDiaTurno);
    destruirArbolBinario(arbolCantidad);

    return 0;
}
