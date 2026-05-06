#include <iostream>
#include "funciones.h"
using namespace std;

// Ejercicio de Torres de Hanoi con recursividad
int main() {
    int numDiscos;
    cout<<"Ingrese el número de discos: "; cin>>numDiscos;
    /*
     * A: Es la torre origen
     * B: Es la torre auxiliar
     * C: Es la torre destino
     */
    cout << "Resultado de Hanoi con: " << numDiscos <<endl;
    hanoi(numDiscos, 'A', 'B', 'C');
    return 0;
}
