#include <iostream>
#include "BibliotecaPilas/funcionesPila.h"
#include "BibliotecaPilas/Pila.h"
using namespace std;

void determinarPosicion(Pila &pila,int *alturas,int n) {
    int alturaMax = -1;
    for (int i = 0; i < n; i++) {
        if (alturas[i]>alturaMax){
            alturaMax = alturas[i];
        }
    }
    // Variables para el problema
    int posUltimoMaximo = -1;
    int izqUltimoMaximo = 0;
    // Variables para la respuesta final
    int maximoTotal = -1;
    int mejorPosicion = -1;
    for (int i = 0; i < n; ++i) {
        int altura = alturas[i];
        if (altura<alturaMax) {
            apilar(pila,{altura});
        }else if (altura == alturaMax) {
            int cantidad = 0;
            while (!esPilaVacia(pila)){
                desapilar(pila);
                cantidad++;
            }
            // Evaluamos el máximo, esta cantidad que vamos a contar son sus elementos a la derecha
            if (posUltimoMaximo!=-1) {
                int totalAnterior = izqUltimoMaximo + cantidad;
                // Si la suma supera al maxi
                if (totalAnterior > maximoTotal) {
                    maximoTotal = totalAnterior;
                    mejorPosicion = posUltimoMaximo;
                }
            }

            posUltimoMaximo = i;
            izqUltimoMaximo = cantidad;
        }
    }
    int cantidadFinal = 0;
    while (!esPilaVacia(pila)) {
        desapilar(pila);
        cantidadFinal++;
    }
    int totalUltimo = izqUltimoMaximo + cantidadFinal;
    if (totalUltimo>maximoTotal) {
        maximoTotal = totalUltimo;
        mejorPosicion = posUltimoMaximo;
    }

    cout<<"Posición: "<<mejorPosicion<<", con ";
    cout<<maximoTotal<<" pilas pequeñas alrededor"<<endl;
}

int main() {
    Pila pila;
    Pila pilaAux;
    construirPila(pila);
    construirPila(pilaAux);
    int alturas[] = {1,7,2,7,3,4,3,2,1,7,2,1,7,3};
    int n = size(alturas);

    determinarPosicion(pila,alturas,n);

    return 0;
}
