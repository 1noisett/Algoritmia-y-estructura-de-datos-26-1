#include <iostream>

#include "BibliotecaArbolBinario/ArbolBinario.h"
#include "BibliotecaArbolBinario/FuncionesArbolBinario.h"
using namespace std;

int main() {
    ArbolBinario arbol, abecedario;
    ArbolBinario arbol1, arbol2, arbol3, arbol4, arbolVacio;
    ArbolBinario hijoIzquierdo, hijoDerecho;

    construir(arbol);
    construir(arbolVacio);

    // ElementoArbolBinario elementoArbol;
    // elementoArbol.numero = 100;
    plantarArbolBinario(arbol1, arbolVacio, {25}, arbolVacio);
    plantarArbolBinario(arbol2, arbolVacio, {80}, arbolVacio);
    plantarArbolBinario(arbol3, arbolVacio, {120}, arbolVacio);
    plantarArbolBinario(arbol4, arbolVacio, {200}, arbolVacio);
    plantarArbolBinario(hijoIzquierdo, arbol1, {50}, arbol2);
    plantarArbolBinario(hijoDerecho, arbol3, {150}, arbol4);
    plantarArbolBinario(arbol, hijoIzquierdo, {100}, hijoDerecho);

    ElementoArbolBinario arreglo[]{
        { 25, 'A'},
        { 50, 'B'},
        { 80, 'C'},
        {100, 'D'},
        {120, 'E'},
        {150, 'F'},
        {200, 'G'}
    };
    int n = sizeof(arreglo)/sizeof(arreglo[0]);

    return 0;
}
