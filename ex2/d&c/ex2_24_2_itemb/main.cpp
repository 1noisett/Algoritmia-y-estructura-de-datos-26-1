#include <iostream>
using namespace std;

struct Plato {
    string nombre;
    int cantidadDisponible;
    int cantidadReservada;
    double porcentajeReservas;
};

/*
 * Particiona el subarreglo [inicio, fin] usando como pivote el ULTIMO elemento
 * (tal como indica el enunciado). Recorre el subarreglo moviendo hacia la zona
 * izquierda todo plato con porcentaje MAYOR al pivote (orden descendente).
 * Al final coloca el pivote en su posicion definitiva y retorna dicha posicion.
 */
int particionar(Plato *arr, int inicio, int fin) {
    // El pivote es el ultimo elemento del subarreglo actual
    double pivote = arr[fin].porcentajeReservas;

    // i marca la frontera de la "zona de mayores":
    // todo lo que este en [inicio, i] ya es mayor que el pivote.
    // Arranca en inicio-1 porque la zona empieza vacia.
    int i = inicio - 1;

    // j recorre hasta fin-1: el pivote (posicion fin) NO se compara consigo mismo
    for (int j = inicio; j < fin; j++) {
        // Orden descendente: los MAYORES van a la izquierda
        if (arr[j].porcentajeReservas > pivote) {
            i++;
            // Se intercambia el struct COMPLETO, no solo el porcentaje,
            // para que nombre y cantidades viajen junto con su valor
            Plato temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // El pivote se coloca justo despues de la zona de mayores:
    // a su izquierda solo hay mayores, a su derecha solo menores o iguales.
    // Esta ya es su posicion final en el arreglo ordenado.
    Plato temp = arr[i + 1];
    arr[i + 1] = arr[fin];
    arr[fin] = temp;

    // Retorna la posicion final del pivote para dividir el problema
    return i + 1;
}


/*
 * Ordena recursivamente el subarreglo [inicio, fin] de mayor a menor.
 * Divide: particionar hace todo el trabajo (O(n)) y fija el pivote.
 * Venceras: se resuelven los dos subproblemas por separado.
 * No hay fase de combinacion: al terminar ambas recursiones el arreglo
 * ya esta ordenado in situ.
 */
void quickSort(Plato *arr, int inicio, int fin) {
    // Caso base: 0 o 1 elementos, no hay nada que ordenar.
    // Tambien cubre los rangos vacios que se generan cuando el pivote
    // queda en un extremo (p-1 < inicio o p+1 > fin).
    if (inicio >= fin) return;

    int p = particionar(arr, inicio, fin);

    // El pivote (posicion p) queda EXCLUIDO de ambas llamadas:
    // cada recursion pierde al menos un elemento, lo que garantiza terminacion.
    quickSort(arr, inicio, p - 1);  // zona de mayores
    quickSort(arr, p + 1, fin);    // zona de menores
}



int main() {
    Plato platos[] = {
        {"Lomo saltado",50,30},
        {"Ceviche",40,35},
        {"Ají de Gallina",30,10},
        {"Causa Limeña",20,20},
        {"Arroz con Pollo",60,45}
    };
    int n = sizeof(platos)/sizeof(platos[0]);
    for (int i = 0; i < n; ++i) {
        platos[i].porcentajeReservas = (double)platos[i].cantidadReservada / platos[i].cantidadDisponible * 100;
    }



    return 0;
}
