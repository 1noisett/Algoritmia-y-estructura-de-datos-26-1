#include <iostream>
#include <fstream>
using namespace std;

#define MAX_FIL 10
#define MAX_COL 7

// PARTE (a)
// Estrategia: busqueda de pico (divide y venceras). Cada fila es unimodal por
// columnas: la radiacion sube hasta el impacto y luego baja. Se compara con el
// vecino derecho: si es menor, el pico esta a la derecha; si no (empate incluido),
// esta en medio o a la izquierda. Devuelve la COLUMNA del valor pico de la fila.
int columnaPico(int *arr,int inicio,int fin) {
    if (inicio == fin) return inicio;
    int medio = inicio + (fin - inicio)/2;

    if (arr[medio] < arr[medio+1]) {
        return columnaPico(arr,medio+1,fin);
    }else {
        return columnaPico(arr,inicio,medio);
    }
}

// PARTE (b)
// Estrategia: busqueda de pico (divide y venceras) bajando por una columna fija,
// la del impacto hallada en la parte (a). Esa columna es unimodal por filas.
// Compara matriz[medio][columna] con matriz[medio+1][columna]. Devuelve la FILA.
int filaPico(int matriz[][MAX_COL], int columna, int inicio, int fin) {
    if (inicio == fin) return inicio;
    int medio = inicio + (fin - inicio)/2;
    if (matriz[medio][columna] < matriz[medio+1][columna]) {
        return filaPico(matriz,columna,medio+1,fin);
    }else {
        return filaPico(matriz,columna,inicio,medio);
    }
}

int main() {
    ifstream input("datos.txt");
    int matriz[MAX_FIL][MAX_COL] = {};
    for (int i = 0; i < MAX_FIL; ++i) {
        for (int j = 0; j < MAX_COL; ++j) {
            input>>matriz[i][j];
        }
    }
    // PARTE (A): potencia maxima y su columna
    int potenciaMax = -1;
    int columna = -1;
    for (int i = 0; i < MAX_FIL; ++i) {
        int colActual = columnaPico(matriz[i],0,MAX_COL-1); // col actual donde la potencia es maxima
        if (matriz[i][colActual] > potenciaMax) {
            potenciaMax = matriz[i][colActual];
            columna = colActual;
        }
    }
    // PARTE (B): fila del impacto
    // usa la columna del impacto maximo de la parte (A) y busca su pico por filas
    int fila = filaPico(matriz,columna,0,MAX_FIL-1);
    cout<<"La potencia máxima más alta de la bomba es "<<potenciaMax<<" y su columna es "<<columna<<endl;
    cout << "La fila con el mayor impacto es " << fila << "." << endl;
    return 0;
}
