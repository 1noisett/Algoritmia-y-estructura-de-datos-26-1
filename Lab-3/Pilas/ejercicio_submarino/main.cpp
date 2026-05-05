#include <iostream>
#include "BibliotecaPilas/funcionesPila.h"
#include "BibliotecaPilas/Pila.h"
using namespace std;

void submarino(Pila &pila,char orden[],int n) {
    //definir el nivel de inicio
    int nivel = 1;
    cout<<"La respuesta sería :";

}
//Hanoi mueve n elementos de una pila a otra, respetando el orden, usando una estructura recursiva y una pila auxiliar
// 1 2 3
// 3 2 1 4
int main() {
    Pila pila;
    construirPila(pila);

    char orden[] = {'B','B','S'};
    int n = size(orden);

    submarino(pila,orden,n);
    return 0;
}
