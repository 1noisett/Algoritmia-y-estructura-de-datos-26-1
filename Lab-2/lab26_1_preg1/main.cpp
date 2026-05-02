#include <iomanip>
#include <iostream>
using namespace std;

#define FIL 10
#define COL 10

int robotArq(int tablero[FIL][COL],int posX,int posY,int fil,int col,int alcance, int dir){
    // CASOS BASE:
    // 1. Si nos salimos de los límites de la matriz
    if (posX>=fil or posX<0 or posY>=col or posY<0) return 0;
    // 2. Si el robot ya agotó su alcance de escaneo
    if (alcance<0) return 0;
    // 3. Si la casilla ya fue visitada, 1 para camino normal y 2 para artefactos ya contados
    if (tablero[posX][posY]==1 or tablero[posX][posY]==2) return 0;

    // PARTE RECURSIVA:
    int artefactosEncontrados = 0;
    if (tablero[posX][posY]==9) {
        artefactosEncontrados = 1;
        tablero[posX][posY] = 2;
    }else {
        tablero[posX][posY] = 1;
    }

    // El total inicia con lo que encontramos en ESTA casilla
    int total = artefactosEncontrados;
    if (dir==1 or dir==0) {
        total += robotArq(tablero, posX-1, posY, fil, col, alcance-1,1); // arriba
        total += robotArq(tablero, posX-1, posY-1, fil, col, alcance-1,1);
        total += robotArq(tablero, posX-1, posY+1, fil, col, alcance-1,1);
    }
    if (dir==-1 or dir==0) {
        total += robotArq(tablero, posX+1, posY, fil, col, alcance-1,-1);// abajo
        total += robotArq(tablero, posX+1, posY-1, fil, col, alcance-1,-1);
        total += robotArq(tablero, posX+1, posY+1, fil, col, alcance-1,-1);
    }


    return total;
}

void imprimirTablero(int tablero[FIL][COL],int fil,int col) {
    for (int i = 0; i < fil; i++) {
        for (int j = 0; j < col; j++) {
            if (tablero[i][j]==2 or tablero[i][j]==1) cout << setw(3) << "*";
            else if (tablero[i][j] == 9) cout << setw(3) << "A";
            else cout << setw(3) << "-";
        }
        cout << endl;
    }
}

int main() {
    int tablero[FIL][COL] = {};
    // Colocamos los artefactos
    tablero[3][3] = 9;
    tablero[3][4] = 9;
    tablero[4][5] = 9;
    tablero[5][4] = 9;
    tablero[5][7] = 9;
    tablero[7][5] = 9;

    // Posiciones iniciales
    int x = 5;
    int y = 5;
    int alcance = 3;

    // Llamamos a la función recursiva y guardamos el resultado
    int total = robotArq(tablero, x, y, FIL, COL, alcance,0);

    // Imprimimos el mensaje de resultado requerido
    cout << "El robot encontro " << total << " artefactos, realizando la siguiente busqueda." << endl;

    // Imprimimos el tablero con el rastro del robot
    imprimirTablero(tablero, FIL, COL);
    return 0;
}
