#include <iostream>
#include <iomanip>
using namespace std;

#define  FIL 6
#define  COL 11

bool robotMinero(int tablero[FIL][COL],int x,int y,int fil,int col,int nivel) {
    // 1. EL ELEVADOR: Si intentamos empezar abajo a la izquierda (y==0)
    // y ya está ocupado, subimos una fila recursivamente.
    if (y==0 and x>=0 and tablero[x][y]!=0) {
        return robotMinero(tablero,x-1,y,fil,col,nivel);
    }

    // 2. LÍMITES: Si nos salimos de la mina, abortar camino.
    if (x<0 or x>=fil or y < 0 or y>=col) return false;
    if (tablero[x][y]!=0) return false;

    // 4. MARCAR: Estamos en una celda válida, dejamos nuestro número.
    tablero[x][y] = nivel;

    // 5. META: Si tocamos el borde derecho, terminamos esta galería.
    if (y == col-1) {
        robotMinero(tablero,fil-1,0,fil,col,nivel+1);// Volvemos al inicio con un nuevo nivel
        return true; // <-- ¡AQUÍ NACE EL TRUE!
    }

    // 6. MOVERSE: Intentamos avanzar. El orden es crucial para que se agrupen bien.
    if (y != 0 and robotMinero(tablero,x+1,y,fil,col,nivel)) return true;//intenta abajo
    if (robotMinero(tablero,x,y+1,fil,col,nivel)) return true;//intenta derecha
    if (robotMinero(tablero,x-1,y,fil,col,nivel)) return true;//intenta arriba

    // 7. BACKTRACKING: Si llegamos aquí, nos atrapamos. Borramos marca y retrocedemos.
    tablero[x][y] = 0;
    return false;
}

void mostrarTablero(int tablero[FIL][COL], int fil, int col) {
    // 1. Recorrer las filas (de arriba hacia abajo)
    for (int i = 0; i < fil; i++) {

        // 2. Recorrer las columnas (de izquierda a derecha)
        for (int j = 0; j < col; j++) {

            // 3. El Traductor: Decidir qué imprimir según el número
            if (tablero[i][j] == 9) {
                // Si es un 9 (la roca secreta del main), imprimimos un asterisco
                cout << setw(3) << "*";

            } else if (tablero[i][j] == 0) {
                // Si es un 0 (nadie pasó por aquí), imprimimos un espacio en blanco
                cout << setw(3) << "-";

            } else {
                // Si es cualquier otro número (1, 2, 3...), imprimimos el número de la galería
                cout << setw(3) << tablero[i][j];
            }
        }
        // 4. Salto de línea: Al terminar una fila, bajamos al siguiente renglón
        cout << endl;
    }
}

int main() {
    int tablero[FIL][COL] = {};//Inicializado el tablero en 0
    //Colocar las rocas
    tablero[FIL-1][5] = 9;
    tablero[FIL-2][5] = 9;
    tablero[FIL-3][5] = 9;

    //Valores iniciales
    int nivel = 1;
    int x = FIL - 1;//Empezados de la fila mas abajo
    int y = 0;

    //Iniciar la recursion
    robotMinero(tablero,x,y,FIL,COL,nivel);

    // Imprimir el resultado final
    mostrarTablero(tablero, FIL, COL);
    return 0;
}