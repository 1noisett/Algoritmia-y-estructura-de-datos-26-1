#include <iostream>

#include "BibliotecaPilas/funcionesPila.h"
#include "BibliotecaPilas/Pila.h"
using namespace std;

bool verificarOrden(int *llegada,int *solicitado,int n) {
    Pila pila;
    construirPila(pila);

    int indiceSolicitado = 0;
    // Leemos el arreglo de llegada de forma secuencial
    for (int i = 0; i < n; ++i) {
        // 1. Llega un contenedor y se apila en el espacio temporal
        ElementoPila elemento;
        elemento.dato = llegada[i];
        apilar(pila,elemento);
        // 2. Verificamos si la cima de la pila es el contenedor que toca entregar
        while (!esPilaVacia(pila) && cima(pila).dato == solicitado[indiceSolicitado]) {
            cout<<desapilar(pila).dato<<" "; // Entregamos el contenedor
            indiceSolicitado++;                 // Avanzamos al siguiente contenedor solicitado
        }
    }
    cout<<endl;
    // 3. Validamos el resultado final
    bool esPosible = esPilaVacia(pila);
    destruirPila(pila);
    return esPosible;
}

int main() {
    int llegada[] = {1,2,3,4};
    int solicitado[] = {1,3,4,2};

    if (verificarOrden(llegada,solicitado,4)) {
        cout<<"Es posible"<<endl;
    }else {
        cout<<"No es posible"<<endl;
    }
    return 0;
}
