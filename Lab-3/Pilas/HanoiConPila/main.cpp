#include <iostream>
#include <numbers>

#include "BibliotecaPilas/funcionesPila.h"
#include "BibliotecaPilas/Pila.h"
using namespace std;

void hanoi(int n,Pila &origen,Pila &auxiliar,Pila &destino) {
    if (n<=0) return;

    if (n==1) {
        apilar(destino,desapilar(origen));
    }else {
        hanoi(n-1,origen,destino,auxiliar);
        apilar(destino,desapilar(origen));
        hanoi(n-1,auxiliar,origen,destino);
    }
}

void fusionarPilas(struct Pila & pilaA, struct Pila &pilaB, struct Pila &pilaC) {
    int cantElementosC;
    ElementoPila elemA;
    ElementoPila elemB;
    while (!esPilaVacia(pilaA) and !esPilaVacia(pilaB)) {
        elemA = cima(pilaA);
        elemB = cima(pilaB);
        cantElementosC = longitudPila(pilaC);

        if (elemA.numero > elemB.numero) {// B es el menor
            hanoi(cantElementosC,pilaC,pilaB,pilaA);
            apilar(pilaC,desapilar(pilaB));
            hanoi(cantElementosC,pilaA,pilaB,pilaC);
        }else {
            hanoi(cantElementosC,pilaC,pilaA,pilaB);
            apilar(pilaC,desapilar(pilaA));
            hanoi(cantElementosC,pilaB,pilaA,pilaC);
        }

    }

    //Bucles de limpieza
    while (!esPilaVacia(pilaA)) {
        cantElementosC = longitudPila(pilaC);
        hanoi(cantElementosC,pilaC,pilaA,pilaB);
        apilar(pilaC,desapilar(pilaA));
        hanoi(cantElementosC,pilaB,pilaA,pilaC);
    }
    while (!esPilaVacia(pilaB)) {
        cantElementosC = longitudPila(pilaC);
        hanoi(cantElementosC,pilaC,pilaA,pilaA);
        apilar(pilaC,desapilar(pilaB));
        hanoi(cantElementosC,pilaA,pilaB,pilaC);
    }
}


int main() {
    //Crear y construir la pila
    Pila pilaA, pilaB,pilaC;
    construirPila(pilaA); construirPila(pilaB); construirPila(pilaC);
    //Agregar los elementos
    apilar(pilaA,{20});
    apilar(pilaA,{15});
    apilar(pilaA,{5});

    apilar(pilaB,{18});
    apilar(pilaB,{12});
    apilar(pilaB,{10});
    apilar(pilaB,{2});
    //Fusionar pilas
    cout<<"INICIO"<<endl;
    fusionarPilas(pilaA,pilaB,pilaC);
    cout<<endl<<"FIN"<<endl;
    cout << "C: " ;imprimirPila(pilaC);

    return 0;
}
