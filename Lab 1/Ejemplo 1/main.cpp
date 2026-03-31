#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Se estudiarán 3 tipos de ordenamiento

// 1. Selection Sort: Busca el elemento más pequeno de la lista y lo intercambia con el
// que está en la primera posicion. Luego busca el segundo más pequeno y asi sucesivamente
//Idea clave: Divide la lista en una parte "ya ordenada" y otra "por ordenar".
//En cada paso, selecciona el mínimo de la parte desordenada.

// 2. Insertion Sort: Este funciona de forma muy similar a como ordenarias una mano de cartas
// Tomás un elemento y lo vas comparando con los anteriores hasta encontrar su lugar exacto,
// desplazando los demás hacia la izquierda
// Idea clave: Es muy eficiente para listas que ya están casi ordenadas o para conjuntos de datos
// muy pequeños.

// 3. Bubble Sort: Los elementos más grandes "burbujean" hacia el final de la lista en cada
// iteracion.

void selectionSort(int array[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n ; j++) {
            if (array[j] < array[minIdx])
                minIdx = j;
        }
        //Intercambiar el minimo encontrado con el primer elemento de la sublista
        int temp = array[i];
        array[i] = array[minIdx];
        array[minIdx] = temp;
    }
}

void insertionSort(int array[], int n) {
    for (int i = 1; i < n; i++) {
        int key = array[i]; //Valor que queremos acomodar
        int j = i - 1; // índice del elemento a la izquierda de la llave
        // Se ejecuta mientras no lleguemos al inicio del arreglo (j >= 0)
        // Y mientras el elemento de la izquierda sea mayor que nuestra llave.
        while (j >= 0 and array[j] > key) {
            array[j + 1] = array[j];// Desplazamos el elemento mayor a la derecha.
            j = j - 1; // Retrocedemos una posición a la izquierda.
        }
        array[j + 1] = key;// Insertamos la llave en su posición correcta.
                            //Se usa 'j + 1' porque el bucle 'j' restó uno de más antes de salir.
    }
}

void bubbleSort(int array[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

int main() {
    int array[] = {5, 2, 9, 1, 5, 6, 8, 4};
    int n = size(array);

    cout << "Elegir algoritmo de ordenamiento:\n";
    cout << "1. Selection Sort\n";
    cout << "2. Insertion Sort\n";
    cout << "3. Bubble Sort\n";
    int algo = 0;
    cin >> algo;
    switch (algo) {
        case 1:
            selectionSort(array, n);
            break;
        case 2:
            insertionSort(array, n);
            break;
        case 3:
            bubbleSort(array, n);
            break;
        default:
            break;
    }

    cout << "Array ordenado: ";
    for (int i = 0; i < n; i++)
        cout << array[i] << " ";

    return 0;
}