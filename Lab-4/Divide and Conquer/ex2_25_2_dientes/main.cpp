#include <iostream>
#include <fstream>
using namespace std;

bool hayCaries(int *densidades, int inicio, int fin, int umbral,
               int &densidadCaries, int &posicionCaries) {
    if (inicio == fin) {                          // caso base: una sola posicion
        if (densidades[inicio] < umbral) {        // esa posicion es caries
            densidadCaries  = densidades[inicio];
            posicionCaries  = inicio;
            return true;
        } else {                                  // no hay caries en este rango
            densidadCaries  = -1;
            posicionCaries  = -1;
            return false;
        }
    }
    int medio = inicio + (fin - inicio) / 2;
    if (densidades[medio] < umbral)               // medio es caries -> medio o izquierda
        return hayCaries(densidades, inicio, medio, umbral, densidadCaries, posicionCaries);
    else                                          // medio sano (>= umbral) -> derecha
        return hayCaries(densidades, medio + 1, fin, umbral, densidadCaries, posicionCaries);
}

int main() {
    int n, t; // n es cantidad de valores y t es el umbral
    cin >> n >> t;

    ifstream input("datos2.txt");
    int densidades[100];
    for (int i = 0; i < n; ++i)
        input >> densidades[i];

    int densidadCaries, posicionCaries;
    if (hayCaries(densidades, 0, n - 1, t, densidadCaries, posicionCaries)) {
        cout << "Primera zona con caries clinica detectada en la posicion "
             << posicionCaries << " (la posicion inicia en 0)" << endl;
        cout << "Densidad registrada: " << densidadCaries << endl;
    } else {
        cout << "No se detecta caries clinica." << endl;
    }
    return 0;
}
