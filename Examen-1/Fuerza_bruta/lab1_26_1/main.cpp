#include <iostream>
using namespace std;

struct Diente {
    int ubicacion;
    int tipo;
    int duracion;
    int ganancia;
    int cantidadCaries;
};

void crearCromosoma(int *cromosoma,int tamano,int num) {
    for(int i=0;i<tamano;i++) {
        cromosoma[i] = num % 4;
        num /= 4;
    }
}

int main() {
    Diente dientes[8] = {
        {1, 1,  5, 20, 3},
        {2, 1,  5, 20, 1},
        {3, 2,  7, 30, 0},
        {4, 3, 10, 35, 1},
        {5, 3, 10, 35, 2},
        {6, 4, 12, 42, 1},
        {7, 4, 12, 42, 2},
        {8, 4, 12, 42, 3},
    };
    // Crear cromosoma
    int n = 8;
    int *cromosoma = new int[n];
    // Combinaciones
    int combinaciones = pow(4,n);
    // Capacidades maximas de las citas en minutos
    int maxCita1 = 60;
    int maxCita2 = 45;
    int maxCita3 = 50;
    int maximoTotal = -1;
    int combinacionGanadora = -1;
    // Lógica fuerza bruta
    for (int i = 0; i < combinaciones; ++i) {
        crearCromosoma(cromosoma,n,i);
        int tiempoCita1 = 0;
        int tiempoCita2 = 0;
        int tiempoCita3 = 0;
        int gananciaActual = 0;
        for (int j = 0; j < n; ++j) {
            // El costo/tiempo total de un diente despues de cuantas caries tenga
            int tiempoDiente = dientes[j].duracion * dientes[j].cantidadCaries;
            int gananciaDiente = dientes[j].ganancia * dientes[j].cantidadCaries;

            if (cromosoma[j]==1) {tiempoCita1 += tiempoDiente; gananciaActual += gananciaDiente;}
            else if (cromosoma[j]==2) {tiempoCita2 += tiempoDiente; gananciaActual += gananciaDiente;}
            else if (cromosoma[j]==3){tiempoCita3 += tiempoDiente; gananciaActual += gananciaDiente;}

            // Validación
            if (tiempoCita1<=maxCita1 && tiempoCita2<=maxCita2 && tiempoCita3<=maxCita3) {
                if (gananciaActual>maximoTotal) {
                    maximoTotal = gananciaActual;
                    combinacionGanadora = i;
                }
            }

        }
    }
    crearCromosoma(cromosoma,n,combinacionGanadora);
    for (int cita = 1; cita <= 3; ++cita) {
        for (int i = 0; i < n; ++i) {
            if (cromosoma[i]==cita) {
                cout<<"Cita: "<<cita<<" Diente: "<<dientes[i].ubicacion<<endl;
            }
        }
    }
    cout<<"La ganancia máxima es: "<<maximoTotal<<endl;
    delete[] cromosoma;
    return 0;
}
