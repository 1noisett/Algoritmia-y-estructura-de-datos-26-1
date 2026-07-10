#include <iostream>

#include "BibliotecaColas/FuncionesCola.h"
using namespace std;

void antenderk(Cola &colaTAD,int k) {
    for (int i = 0; i < k; ++i) {
        if (!esColaVacia(colaTAD)) {
            ElementoCola e = desencolar(colaTAD);
            string tipo;
            if (e.prioridad==1) tipo="P1";
            else tipo="P2";
            cout<<e.dato<<" ("<<tipo<<")"<<endl;
        }
    }
}

int main() {
    // resolver 2 ejercicios de ab
    // repasar abb iterativo
    // repasar d&c
    Cola cola;
    construirCola(cola);
    ElementoCola e;
    e = {1001,2};
    encolar(cola,e);
    e = {1002,1};
    encolar(cola,e);

    // antenderk(cola,1);
    antenderk(cola,1);

    e = {1004,2};
    encolar(cola,e);

    e = {1005,1};
    encolar(cola,e);
    imprimir(cola);
    cout<<endl<<endl;

    antenderk(cola,3);

    // repasar
    return 0;
}
