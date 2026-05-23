#include <iostream>

#include "BibliotecaPilas/funcionesPila.h"
#include "BibliotecaPilas/Pila.h"

using namespace std;

#define FIL 4
#define COL 4

int main() {
    Pila pila;
    construirPila(pila);

    // Matriz de entrada (no se modifica)
    int matriz[FIL][COL] = {
        {1, 1, 1, 0},
        {1, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 0}
    };

    // Arreglo unidimensional y variable de área
    int memoriaTemporal[COL] = {0};
    int areaMaxima = 0;

    // Iteramos sobre las filas del jardín
    for (int i = 0; i < FIL; i++) {

        // PASO A: Actualizamos el arreglo unidimensional (nuestra memoria temporal)
        for (int j = 0; j < COL; j++) {
            if (matriz[i][j] == 1) {
                memoriaTemporal[j] += 1;
            } else {
                memoriaTemporal[j] = 0;
            }
        }

        // PASO B: Calculamos el área máxima usando la Pila para la fila actual
        int j = 0;
        while (j < COL) {
            // Si la pila está vacía o la altura actual es mayor o igual a la de la cima
            if (esPilaVacia(pila)) {
                ElementoPila elem;
                elem.dato = j;
                apilar(pila, elem);
                j++;
            } else {
                ElementoPila elemCima = cima(pila);
                if (memoriaTemporal[j] >= memoriaTemporal[elemCima.dato]) {
                    ElementoPila elem;
                    elem.dato = j;
                    apilar(pila, elem);
                    j++;
                } else {
                    // Si encontramos una altura menor, calculamos el área del rectángulo
                    // con la altura del tope de la pila
                    ElementoPila tope = desapilar(pila);

                    int ancho;
                    if (esPilaVacia(pila)) {
                        ancho = j;
                    } else {
                        ancho = j - cima(pila).dato - 1;
                    }

                    int areaActual = memoriaTemporal[tope.dato] * ancho;
                    if (areaActual > areaMaxima) {
                        areaMaxima = areaActual;
                    }
                }
            }
        }

        // Vaciamos los elementos restantes en la pila al terminar la fila
        while (!esPilaVacia(pila)) {
            ElementoPila tope = desapilar(pila);

            int ancho;
            if (esPilaVacia(pila)) {
                ancho = j;
            } else {
                ancho = j - cima(pila).dato - 1;
            }

            int areaActual = memoriaTemporal[tope.dato] * ancho;
            if (areaActual > areaMaxima) {
                areaMaxima = areaActual;
            }
        }
    }

    // Destruimos la pila para liberar memoria antes de terminar
    destruirPila(pila);

    cout << "El area maxima que el ROBOTJARDIN puede cortar es: " << areaMaxima << endl;

    return 0;
}