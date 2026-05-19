#include <iostream>
using namespace std;

struct Recurso {
    int codigoAlerta;
    int prioridad;
    int horaInicio;
    int duracion;
};

void crearCromosoma(int *cromosoma,int tamano,int combinacion) {
    for (int i = 0; i < tamano; ++i) {
        cromosoma[i] = combinacion%2;
        combinacion /= 2;
    }
}

// Turno de trabajo de 8:00 a 17:00 sin trabajar de 13:00 a 14:00
// Alertas de prioridad 1 requiere una hora adicional
// Dos intervalos se traslapan ⟺ cada uno empieza antes de que el otro termine.

int main() {
    Recurso recurso[13] = {
        {1801, 2, 8, 1},
        {1802, 1, 8, 1},
        {1803, 1, 9, 1},
        {1804, 3, 9, 3},
        {1805, 1, 10, 1},
        {1806, 1, 11, 1},
        {1807, 3, 12, 1},
        {1808, 1, 14, 1},
        {1809, 2, 14, 2},
        {1810, 3, 14, 1},
        {1811, 2, 15, 1},
        {1812, 3, 16, 1},
        {1813, 2, 16, 2}
    };
    int p1,p2,p3;
    cin >> p1 >> p2 >> p3;

    int tamano = 13;
    int *cromosoma = new int[tamano];
    int combinaciones = 1 << tamano;

    // Arreglos auxiliares para guardar los intervalos [ini, fin) de las
    // alertas seleccionadas en la combinacion actual y poder detectar traslapes.
    int inicioAlerta[13];
    int finAlerta[13];

    for (int i = 0; i < combinaciones; ++i) {
        crearCromosoma(cromosoma,tamano,i);

        bool valido = true;
        int nump1 = 0, nump2 = 0, nump3 = 0;
        int numSeleccionadas = 0;

        // Procesa cada alerta marcada en el cromosoma
        for (int j = 0; j < tamano && valido; ++j) {
            if (cromosoma[j]==1) {
                int ini = recurso[j].horaInicio;
                int fin = ini + recurso[j].duracion;
                if (recurso[j].prioridad == 1) fin += 1;

                // Validacion 1: debe caber en el turno [8, 17)
                if (!(ini>=8 and fin <=17)) { valido = false; break;}

                // Validacion 2: no debe traslaparse con el almuerzo [13, 14)
                if (!(ini>=14 or fin<=13)) { valido = false; break;}

                // Validacion 3: no debe traslaparse con alertas ya seleccionadas
                // Dos intervalos [a,b) y [c,d) se traslapan si: a < d && c < b (2,4) (5,8)
                for (int k = 0; k < numSeleccionadas; ++k) {
                    if (ini < finAlerta[k] && inicioAlerta[k] < fin) {
                        valido = false; break;
                    }
                }
                if (!valido) break;

                // Si paso todas las validaciones, se guarda y se cuenta
                inicioAlerta[numSeleccionadas] = ini;
                finAlerta[numSeleccionadas] = fin;
                numSeleccionadas++;

                if (recurso[j].prioridad == 1) nump1++;
                else if (recurso[j].prioridad == 2) nump2++;
                else nump3++;
            }
        }
        if (valido && nump1 == p1 and nump2 == p2 and nump3 == p3) {
            crearCromosoma(cromosoma,tamano,i);
            for (int l = 0; l < tamano; ++l) {
                if (cromosoma[l]==1)
                    cout<<recurso[l].codigoAlerta<<" P"<<recurso[l].prioridad<<" | ";
            }

        }
    }
    delete[] cromosoma;
    return 0;
}
