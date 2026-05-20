#include <iostream>

#include "BibliotecaPilas/funcionesPila.h"
#include "BibliotecaPilas/Pila.h"
using namespace std;

struct SistemaPilas {
    Pila principal;
    Pila extra;
};

void construirSistema(SistemaPilas &pila) {
    construirPila(pila.principal);
    construirPila(pila.extra);
}

void nuevoApilar(SistemaPilas &pila, int numLote) {
    ElementoPila elemento;
    elemento.dato = numLote;

    apilar(pila.principal, elemento);
    if (esPilaVacia(pila.extra) || numLote<=cima(pila.extra).dato) {
        apilar(pila.extra,elemento);
    }else {
        apilar(pila.extra,cima(pila.extra));
    }
}

ElementoPila nuevoDesapilar(SistemaPilas &pila) {
    desapilar(pila.extra);
    ElementoPila elemento = desapilar(pila.principal);
    return elemento;
}

ElementoPila minimo(SistemaPilas &pila) {
    return cima(pila.extra);
}

int main() {
    SistemaPilas pila;
    construirSistema(pila);

    nuevoApilar(pila,201809);
    nuevoApilar(pila,202010);
    nuevoApilar(pila,202109);
    nuevoApilar(pila,201510);
    nuevoApilar(pila,202409);

    cout<<minimo(pila).dato<<endl;

    nuevoDesapilar(pila);
    nuevoDesapilar(pila);

    cout<<endl;
    cout<<minimo(pila).dato<<endl;

    return 0;
}

