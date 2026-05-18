#include <iostream>

#include "BibliotecaColas/Cola.h"
#include "BibliotecaColas/FuncionesCola.h"
using namespace std;

void atenderK(Cola &colaTAD,int k) {
    for (int i = 0; i < k; ++i) {
        if (!esColaVacia(colaTAD)) {
            ElementoCola atendido = desencolar(colaTAD);
            string tipo;
            if (atendido.prioridad==1) tipo = "P1";
            else tipo = "P2";
            cout<<"Atendido: "<<atendido.id<<" ("<<tipo<<")"<<endl;
        }
    }
}

int main() {
    Cola colaTAD;
    construirCola(colaTAD);

    // llegada 1001 regular
    ElementoCola e1 = {1001,2}; encolar(colaTAD,e1);

    // llegada 1002 preferente
    ElementoCola e2 = {1002,1}; encolar(colaTAD,e2);

    // atender 1
    atenderK(colaTAD,1);

    // llegada 1004 regular
    ElementoCola e3 = {1004,2}; encolar(colaTAD,e3);

    // llegada 1005 preferente
    ElementoCola e4 = {1005,1}; encolar(colaTAD,e4);

    // imprimir
    imprimir(colaTAD);

    // atender 3
    atenderK(colaTAD,3);

    // imprimir
    imprimir(colaTAD);

    return 0;
}
