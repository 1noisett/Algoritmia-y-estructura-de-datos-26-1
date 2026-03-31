#include <cmath>
#include <iostream>
#include <math.h>
using namespace std;

void cargarCromosoma(int *cromosoma, int tamanoCromosoma, int numComb) {
    for (int i = 0; i < tamanoCromosoma; i++) {
        cromosoma[i] = numComb % 2;
        numComb = numComb / 2;
    }
}

int main() {
    int paq[] = {2,12,4,8,1,6,5};
    int tamanoCromosoma = sizeof(paq)/sizeof(paq[0]);
    //Crear cromosoma
    int *cromosoma = new int[tamanoCromosoma];
    int combinaciones = pow(2,tamanoCromosoma);
    int mejorCromosoma = 0;
    int mejorPeso = 0;
    for(int i = 0; i < combinaciones; i++) {
        cargarCromosoma(cromosoma, tamanoCromosoma, i);
        int sumaParcial = 0;
        for(int j = 0; j < tamanoCromosoma; j++) {
            sumaParcial += paq[j]*cromosoma[j];
        }
        if (sumaParcial<=15 and mejorPeso<sumaParcial) {
            mejorCromosoma = i;
            mejorPeso = sumaParcial;
        }
    }
    cout<<"Mejor cromosoma: "<<mejorCromosoma<<endl;
    cout<<"Mejor peso: "<<mejorPeso<<endl;
    return 0;
}
