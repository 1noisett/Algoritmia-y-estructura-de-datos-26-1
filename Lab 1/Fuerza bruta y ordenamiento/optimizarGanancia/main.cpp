#include <cmath>
#include <iostream>
using namespace std;

void cargarCromosoma(int *cromosoma, int tamanoCromosoma, int numComb) {
    for (int i = 0; i < tamanoCromosoma; i++) {
        cromosoma[i] = numComb % 2;
        numComb = numComb / 2;
    }
}

int main() {
    // int peso[] = {8,2,10,10,5,5};
    // int ganancia[] = {15,20,5,10,8,5};
    int matriz[][2] = {{8,15}, {2,20}, {10,5}, {10,10}, {5,8}, {5,5}};
    //crear cromosoma
    int tamanoCromosoma = 6;
    int *cromosoma = new int[tamanoCromosoma];
    int combinaciones = pow(2,tamanoCromosoma);
    int gananciaMaxima = 0;
    int mejorCombinacion = 0;
    for (int i = 0; i < combinaciones; i++) {
        cargarCromosoma(cromosoma, tamanoCromosoma,i);
        int sumaGanancia = 0;
        int sumaPeso = 0;
        for (int j = 0; j < tamanoCromosoma; j++) {
            sumaGanancia += cromosoma[j] * matriz[j][1];
            sumaPeso += cromosoma[j] * matriz[j][0];
        }
        if (sumaPeso <= 25 and gananciaMaxima < sumaGanancia) {
            gananciaMaxima = sumaGanancia;
            mejorCombinacion = i;
        }
    }
    cout << gananciaMaxima << endl;
    cargarCromosoma(cromosoma, tamanoCromosoma, mejorCombinacion);
    for (int j = 0; j < tamanoCromosoma; j++) {
        if (cromosoma[j] == 1) {
            cout << j+1 << " ";
        }
    }

    delete[] cromosoma;
    return 0;
}