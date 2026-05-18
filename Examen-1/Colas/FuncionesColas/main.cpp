#include <iostream>

#include "BibliotecaColas/Cola.h"
#include "BibliotecaColas/FuncionesCola.h"
using namespace std;

int main() {
    Cola cola;
    construirCola(cola);

    ElementoCola elemento;
    for (int i = 0; i < 20; i+=3) {
        elemento.dato = i;
        encolar(cola, elemento);
    }

    imprimir(cola);

    //Desencolamos elementos de la cola
    while (!esColaVacia(cola)) {//mientras la cola no este vacia
        elemento = desencolar(cola);
        cout << "Desencolando: "<< elemento.dato << endl;
    }
    imprimir(cola);
    return 0;
}
