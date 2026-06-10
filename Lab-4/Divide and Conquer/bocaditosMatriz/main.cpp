#include <iostream>
#include <fstream>
using namespace std;

#define MAXF 10   // tope de filas de pasajeros
#define MAXC 11   // tope de bocaditos/asientos por fila

char letraBocadito(int codigo) {
    if (codigo == 1) return 'O';
    if (codigo == 2) return 'C';
    if (codigo == 3) return 'A';
    if (codigo == 4) return 'E';
    if (codigo == 5) return 'R';
    if (codigo == 6) return 'F';
    if (codigo == 7) return 'B';

    return '?';
}

int encontrarUnicoElemento(int *arr,int inicio,int fin) {
    if (inicio==fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;

    if (medio%2==0) {
        if (arr[medio]==arr[medio+1]) {
            return encontrarUnicoElemento(arr,medio+2,fin);
        }else {
            return encontrarUnicoElemento(arr,inicio,medio);
        }
    }else {
        if (arr[medio]==arr[medio-1]) {
            return encontrarUnicoElemento(arr,medio+1,fin);
        }else {
            return encontrarUnicoElemento(arr,inicio,medio);
        }
    }
}

int encontrarMaximoValor(int *arr,int inicio,int fin) {
    if (inicio==fin) return inicio;
    int medio = inicio + (fin-inicio)/2;

    if (arr[medio]<arr[medio+1]) {
        return encontrarMaximoValor(arr,medio+1,fin);
    }else {
        return encontrarMaximoValor(arr,inicio,medio);
    }
}

int main() {
    int m;                       // cantidad de filas de pasajeros (dato de entrada)
    int bocaditos[MAXF][MAXC];   // matriz brindada (parte a)
    int precios[MAXF][MAXC];     // matriz brindada (parte b)

    ifstream input("datos.txt");

    // ---------- PARTE (a): matriz de bocaditos ----------
    // Entrada: m, y por cada fila su cantidad de bocaditos seguida de los codigos.
    // Se procesa cada fila apenas se lee, por eso no hace falta guardar los largos.
    input >> m;
    cout << "Correccion de combos:" << endl;
    for (int i = 0; i < m; ++i) {
        int cantidad;
        input >> cantidad;
        for (int j = 0; j < cantidad; ++j) input >> bocaditos[i][j];
        // Fila errada = cantidad impar (un bocadito de mas, que forma el triple).
        if (cantidad % 2 != 0) {
            int bocadExtra = encontrarUnicoElemento(bocaditos[i], 0, cantidad - 1);
            cout << "La fila " << (i + 1) << " tiene un "
                 << letraBocadito(bocadExtra) << " adicional" << endl;
        }
    }

    // ---------- PARTE (b): matriz de precios ----------
    // Entrada: n (asientos por fila) y luego m filas de n precios.
    int n;
    input >> n;
    cout << endl;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) input >> precios[i][j];
        int asiento = encontrarMaximoValor(precios[i], 0, n - 1) + 1; // a 1-indexado
        cout << "En la fila " << (i + 1) << ", el pasajero del asiento "
             << asiento << " tiene el bocadito mas caro que sus 2 vecinos" << endl;
    }

    return 0;
}

/*
8
11 1 1 2 2 3 3 4 4 5 5 5
10 2 2 3 3 5 5 4 4 7 7
10 5 5 4 4 2 2 6 6 3 3
11 4 4 6 6 3 3 3 7 7 5 5
11 2 2 2 3 3 5 5 1 1 4 4
10 1 1 2 2 3 3 5 5 4 4
10 3 3 6 6 5 5 4 4 1 1
10 4 4 3 3 1 1 7 7 6 6
5
1 2 3 2 1
2 3 2 2 1
1 2 2 5 3
2 5 3 3 1
2 2 3 2 1
1 2 3 2 1
3 5 2 1 1
2 3 2 1 1
*/