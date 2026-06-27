#include <iostream>
#include "BibliotecaArbolBinario/ArbolBinario.h"
#include "BibliotecaArbolBinario/FuncionesArbolBinario.h"
using namespace std;

/*
 * DIVIDE & CONQUER (D&C) -> ver llenarArbolRecursivo
 *
 * Fin: a partir de un arreglo YA ORDENADO, construir un BST BALANCEADO.
 * Si insertaramos los elementos uno por uno (A,B,C,...), como cada uno es
 * mayor que el anterior, todos se irian a la derecha y el arbol quedaria
 * degenerado (una lista, altura O(n) -> lento). D&C lo evita: toma el
 * elemento del MEDIO como raiz, dejando mitad de menores a la izquierda
 * y mitad de mayores a la derecha. Asi el arbol queda con altura minima
 * O(log n).
 *
 * Los tres pasos del patron D&C:
 *   - Divide:   parto el rango [inicio, fin] en dos mitades alrededor de "medio".
 *   - Venceras: resuelvo cada mitad con la MISMA funcion (recursion); cada
 *               mitad construye su propio subarbol.
 *   - Combina:  cuelgo las soluciones de nodo->izq y nodo->der.
 *
 * Traza con el arreglo A..G (indices 0..6):
 *   (0,6) medio=3 -> D es la raiz
 *      |- izq (0,2) medio=1 -> B
 *      |     |- izq (0,0) medio=0 -> A
 *      |     |- der (2,2) medio=2 -> C
 *      |- der (4,6) medio=5 -> F
 *            |- izq (4,4) medio=4 -> E
 *            |- der (6,6) medio=6 -> G
 *
 *           D
 *         /   \
 *        B     F
 *       / \   / \
 *      A   C E   G
 *
 * Por eso: recorrido por niveles -> D B F A C E G
 *          recorrido en orden     -> A B C D E F G  (un BST en orden sale ordenado)
 */

void llenarArbolRecursivo(NodoArbolBinario *&nodo,ElementoArbolBinario *arreglo,int inicio,int fin) {
    // estrategia D&C, rango inclusivo [inicio, fin]
    if (inicio>fin) return;                                                               // 1. caso base: rango vacío
    int medio = inicio + (fin-inicio)/2;                                                 // 2. elijo el medio
    plantarNodoArbolBinario(nodo,nullptr,{arreglo[medio]},nullptr);  // 3. lo hago raíz
    llenarArbolRecursivo(nodo->izq,arreglo,inicio,medio-1);                       // 4. mitad izq -> subarbol izq
    llenarArbolRecursivo(nodo->der,arreglo,medio+1,fin);                        // 5. mitad der -> subarbol der
}

void llenarArbol(ArbolBinario &arbol,ElementoArbolBinario *arreglo,int inicio,int fin) {
    llenarArbolRecursivo(arbol.raiz,arreglo,inicio,fin);
}

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
    construir(abecedario);
    // este sirve para árboles ABB
    llenarArbol(abecedario, arreglo, 0, n - 1);

    cout << "Recorrer en En orden: " << endl;
    recorrerInOrder(abecedario);
    cout << endl;

    cout << "Recorrer en Pre orden: " << endl;
    recorrerPreOrder(arbol);
    cout << endl;

    cout << "Recorrer en Post orden: " << endl;
    recorrerPostOrder(arbol);
    cout << endl;

    cout << "Numero de hojas: " << numeroHojas(arbol) << endl;
    cout << "Numero de nodos: " << numeroNodos(arbol) << endl;
    cout << "Altura arbol: " << altura(arbol) << endl;
    cout << "Es equilibrado: " << esEquilibrado(arbol) << endl;

    cout << endl <<"Imprimir por niveles: " << endl;
    recorrerPorNiveles(abecedario);
    cout<<endl<<"Imprimir por niveles con cambio de línea: "<<endl;
    recorrerPorNivelCambioLinea(abecedario);

    cout<<"Recorrer In Order abecedario: "<<endl;
    recorrerInOrder(abecedario);
    return 0;
}
