#include <cmath>
#include <iostream>
#include <math.h>
using namespace std;

void crearCromosoma(int *cromosoma, int tamanoCromosoma, int combinacion) {
    for (int i = 0; i < tamanoCromosoma; i++) {
        cromosoma[i] = combinacion % 3;
        combinacion = combinacion / 3;
    }
}

void imprimirCromosoma(int *cromosoma, int tamanoCromosoma, int numDisco) {
    cout << "Disco " << numDisco << ": ";
    for (int i = 0; i < tamanoCromosoma; i++) {
        if (cromosoma[i] + 1 == numDisco) {
            cout << i + 1 << " ";
        }
    }
    cout << endl;
}

int main() {
    int tablas[] = {150, 100, 80, 50, 120, 10};
    int v_discos_inicial[] = {250, 200, 200};
    int tamanoCromosoma = 6;
    //Crear cromosoma
    int *cromosoma = new int[tamanoCromosoma];
    int combinaciones = pow(3, tamanoCromosoma);

    int mejorMinimoGlobal = -99999; // Queremos que el "peor" sea lo más alto posible
    int combinacionOptima = -1;

    for (int i = 0; i < combinaciones; i++) {
        crearCromosoma(cromosoma, tamanoCromosoma,i);
        int cargaDiscos[3] = {0,0,0};
        // Sumamos la velocidad (IOPs) de cada tabla al disco que le tocó
        for (int j = 0; j < tamanoCromosoma; j++) {
            cargaDiscos[cromosoma[j]] += tablas[j];
        }
        int v_final[3];
        v_final[0] = v_discos_inicial[0] - cargaDiscos[0];
        v_final[1] = v_discos_inicial[1] - cargaDiscos[1];
        v_final[2] = v_discos_inicial[2] - cargaDiscos[2];
        //Cuál es el disco que quedo peor(con menor velocidad)
        //Este valor representa la calidad de esta combinación específica
        int minimoActual = min(v_final[0], min(v_final[1], v_final[2]));
        //Si el disco más lento de ESTA combinación es mejor(más rápido)
        //que el disco más lento de la mejor combinación anterior
        if (minimoActual > mejorMinimoGlobal) {
            mejorMinimoGlobal = minimoActual;
            combinacionOptima = i;
        }
    }

    crearCromosoma(cromosoma, tamanoCromosoma, combinacionOptima);
    //Imprimimos la solución
    imprimirCromosoma(cromosoma, tamanoCromosoma, 1);
    imprimirCromosoma(cromosoma, tamanoCromosoma, 2);
    imprimirCromosoma(cromosoma, tamanoCromosoma, 3);

    cout << "\nCalidad de la solucion (Velocidad del disco mas lento): " << mejorMinimoGlobal << " IOPs" << endl;

    delete[] cromosoma;
    return 0;
}