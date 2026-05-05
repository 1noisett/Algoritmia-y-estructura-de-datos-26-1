#include <iostream>
#include "BibliotecaPilas/funcionesPila.h"
#include "BibliotecaPilas/Pila.h"
using namespace std;

void pasaPila(Pila &origen,Pila &destino) {
    if (esPilaVacia(origen)) {
        destino.inicio = nullptr;
        return;
    }else {
        while (!esPilaVacia(origen)) {
            ElementoPila elemento = desapilar(origen);
            int n = 0;
            while (!esPilaVacia(origen)) {
                apilar(destino,elemento);
                elemento = desapilar(origen);
                n++;
            }
            //Regresar elementos estorbo
            while (n>0) {
                apilar(origen,desapilar(destino));
                n--;
            }
            apilar(destino,elemento);
        }
    }
    cout<<endl;
    imprimirPila(destino);
}

int main() {
    Pila pila;
    construirPila(pila);
    for (int i = 0; i < 10; ++i) {
        ElementoPila elemento;
        elemento.dato = i;
        apilar(pila,elemento);
    }
    imprimirPila(pila);
    //Crear pila aux
    Pila pilaAux;
    construirPila(pilaAux);
    pasaPila(pila,pilaAux);
    return 0;
}
