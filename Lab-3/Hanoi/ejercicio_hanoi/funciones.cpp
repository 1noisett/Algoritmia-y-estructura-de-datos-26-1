//
// Created by Miguel Bazan on 5/05/26.
//

#include "funciones.h"

#include <iostream>
#include <ostream>
using namespace std;

/*
 * Tú solo escribes el plan de un nivel: "delego los de arriba al auxiliar,
 * muevo el grande al destino, traigo los de arriba desde el auxiliar".
 * No te importa qué torre es el auxiliar en términos absolutos,
 * te importa que existe un espacio temporal donde estacionar los discos pequeños
 * mientras liberas al grande. La recursión se encarga de que en cada subnivel
 * ese "auxiliar" sea la torre que toque.
 */

void hanoi(int n, char origen, char auxiliar, char destino) {
    if (n==1) {
        moverUnDisco(n, origen, destino);
    }else {
        //Paso 1: Llevo n-1 discos de A hacia B, usando C como auxiliar
        hanoi(n-1, origen, destino, auxiliar);
        //Paso 2: El disco más grande queda libre, lo muevo a su destino
        moverUnDisco(n,origen,destino);
        //Paso 3: Llevo n-1 discos de B hacia C, usando A como auxiliar
        hanoi(n-1,auxiliar,origen,destino);
    }
}

void moverUnDisco(int n, char origen, char destino) {
    cout << "Mover disco " << n << " desde la torre " << origen << " hacia la torre " << destino << endl;
}