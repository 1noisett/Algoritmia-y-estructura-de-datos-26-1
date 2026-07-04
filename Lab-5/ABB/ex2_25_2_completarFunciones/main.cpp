#include <iostream>
#include "BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h"

using namespace std;

void insertarNumero(ArbolBinarioBusqueda &arbol, int numero) {
    ElementoArbolBinarioBusqueda elemento{};
    elemento.numero = numero;
    insertar(arbol, elemento);
}

void eliminarNumero(ArbolBinarioBusqueda &arbol, int numero) {
    ElementoArbolBinarioBusqueda elemento{};
    elemento.numero = numero;
    eliminar(arbol, elemento);
}

int main() {
    ArbolBinarioBusqueda arbol;
    construir(arbol);

    // Arbol del enunciado, in-order: 3 5 8 10 13 15 20
    int valores[] = {10, 5, 15, 3, 8, 13, 20};
    for (int v : valores)
        insertarNumero(arbol, v);

    cout << "=== ITEM 1: insertar ===" << endl;
    cout << "InOrder (debe salir ordenado): ";
    recorrerInOrder(arbol);
    cout << endl;
    cout << "Insertando duplicado (10): ";
    insertarNumero(arbol, 10);
    cout << "size de la raiz: " << tamanoNodo(arbol.raiz) << " (esperado 7)" << endl;

    cout << endl << "=== ITEM 2: k_esimo_menor ===" << endl;
    for (int k = 1; k <= 7; k++)
        cout << "k=" << k << " -> " << k_esimo_menor(arbol.raiz, k) << endl;
    cout << "k=0 (invalido) -> " << k_esimo_menor(arbol.raiz, 0) << endl;
    cout << "k=8 (invalido) -> " << k_esimo_menor(arbol.raiz, 8) << endl;

    cout << endl << "=== ITEM 3: mediana ===" << endl;
    cout << "n=7 (impar), mediana: " << mediana(arbol.raiz) << " (esperado 10)" << endl;

    cout << endl << "=== ITEM 1: eliminar (hoja, un hijo, dos hijos) ===" << endl;
    eliminarNumero(arbol, 3);   // hoja
    cout << "Sin 3 (hoja):     ";
    recorrerInOrder(arbol);
    cout << endl;
    eliminarNumero(arbol, 5);   // le queda solo el hijo 8
    cout << "Sin 5 (un hijo):  ";
    recorrerInOrder(arbol);
    cout << endl;
    eliminarNumero(arbol, 10);  // raiz con dos hijos
    cout << "Sin 10 (2 hijos): ";
    recorrerInOrder(arbol);
    cout << endl;
    cout << "size de la raiz: " << tamanoNodo(arbol.raiz) << " (esperado 4)" << endl;
    cout << "n=4 (par), mediana: " << mediana(arbol.raiz) << " (esperado 14, promedio de 13 y 15)" << endl;

    cout << endl << "=== Arbol vacio ===" << endl;
    destruirArbolBinario(arbol);
    cout << "mediana de arbol vacio: ";
    mediana(arbol.raiz);

    return 0;
}
