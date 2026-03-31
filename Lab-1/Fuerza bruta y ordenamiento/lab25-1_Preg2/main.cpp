#include <iostream>
using namespace std;

struct Recurso {
    int id;
    int costo;
    int nivelSeguridad;
    int dependencias[3];
    int numDependencias;
};

void crearCromosoma(int *cromosoma, int tamanoCromosoma, int numeroCromosoma) {
    for (int i = 0; i < tamanoCromosoma; i++) {
        cromosoma[i] = numeroCromosoma % 2;
        numeroCromosoma = numeroCromosoma / 2;
    }
}

bool verificarDependencias(int *cromosoma, Recurso *lista, int tamano) {
    for (int i = 0; i < tamano; i++) {
        if (cromosoma[i] == 1) {
            for (int d = 0; d < lista[i].numDependencias; d++) {
                int indxDependencia = lista[i].dependencias[d];
                if (cromosoma[indxDependencia] == false) return false;
            }
        }
    }
    return true;
}

int main() {
    Recurso lista[10] = {
        {1, 50, 120, {}, 0},
        {2, 40, 110, {}, 0},
        {3, 80, 140, {}, 0},
        {4, 70, 130, {0}, 1},
        {5, 85, 160, {0}, 1},
        {6, 140, 250, {0, 1}, 2},
        {7, 55, 100, {1}, 1},
        {8, 130, 240, {1, 2}, 2},
        {9, 30, 90, {}, 0},
        {10, 150, 300, {0, 1, 4}, 3}
    };
    //Crear cromosoma
    int tamano = 10;
    int *cromosoma = new int[tamano];
    int combinaciones = 1 << tamano;

    int presupuesto = 100;
    int presupuestoMinimo = 0.8 * presupuesto;
    int mejorCombinacion = -1;
    for (int i = 0; i < combinaciones; i++) {
        crearCromosoma(cromosoma, tamano,i);
        int costoTotal = 0;
        for (int j = 0; j < tamano; j++) {//Obtengo el costo total de la combinacion
            costoTotal += cromosoma[j] * lista[j].costo;
        }

        if (costoTotal >= presupuestoMinimo && costoTotal <= presupuesto) {//Filtro 1: presupuesto

            if (verificarDependencias(cromosoma,lista,tamano)) {//Filtro 2: Dependencias
                //Salida formateada
                cout << "Combinación " << i << ": Recursos: ";
                for (int j = 0; j < tamano; j++) {
                    if (cromosoma[j]==1) cout << "R" << lista[j].id<< " ";
                }
                cout << "| Costo: " << costoTotal << " miles" << endl;
            }

        }
    }
    delete[] cromosoma;
    return 0;
}