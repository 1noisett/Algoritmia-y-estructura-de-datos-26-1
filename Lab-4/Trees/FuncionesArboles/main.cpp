#include <iostream>
#include "BibliotecaArbolBinario/ArbolBinario.h"
#include "BibliotecaArbolBinario/FuncionesArbolBinario.h"
using namespace std;

int main() {
    ArbolBinario arbol,arbolVacio;
    ArbolBinario subarbol25,subarbol80,subarbol120,subarbol200;
    ArbolBinario hijoIzq,hijoDer;

    /*               100              Nivel 0 (más alto)
     *             /     \
     *           50      150          Nivel 1
     *         /   \    /   \
     *       25    80  120   200      Nivel 2 (más bajo)
     */
    construir(arbol);
    construir(arbolVacio); // para plantar con nullptr

    // una forma de crear un árbol es plantando desde el nivel más bajo, pero no es la única
    // los árboles binarios tienen criterios para plantar los nodos
    plantarArbolBinario(subarbol25,arbolVacio,{25},arbolVacio);
    plantarArbolBinario(subarbol80,arbolVacio,{80},arbolVacio);
    plantarArbolBinario(subarbol120,arbolVacio,{120},arbolVacio);
    plantarArbolBinario(subarbol200,arbolVacio,{200},arbolVacio);
    plantarArbolBinario(hijoIzq,subarbol25,{50},subarbol80);
    plantarArbolBinario(hijoDer,subarbol120,{150},subarbol200);
    plantarArbolBinario(arbol,hijoIzq,{100},hijoDer);
    // Recorridos
    cout<<"Recorrido Pre Order:"<<endl;
    recorrerPreOrder(arbol);
    cout<<endl<<"Recorrido In Order:"<<endl;
    recorrerInOrder(arbol);
    cout<<endl<<"Recorrido Post Order:"<<endl;
    recorrerPostOrder(arbol);
    // Número de nodos y hojas
    cout<<endl<<"Número de nodos: "<<numeroNodos(arbol);
    cout<<endl<<"Número de hojas: "<<numeroHojas(arbol);
    // Altura del árbol
    cout<<endl<<"Altura del árbol: "<<altura(arbol);
    // Es equilibrado?
    cout<<endl<<"Es equilibrado: "<<esEquilibrado(arbol)<<endl;


    return 0;
}
