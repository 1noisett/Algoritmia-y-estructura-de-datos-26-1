#include <iostream>
#include "BibliotecaPilas/funcionesPila.h"
#include "BibliotecaPilas/Pila.h"
using namespace std;

int main() {
    Pila pila;
    construirPila(pila);
    for (int i = 0; i < 10; ++i) {
        ElementoPila elemento;
        elemento.dato = i;
        apilar(pila,elemento);
    }
    imprimirPila(pila);

    return 0;
}
