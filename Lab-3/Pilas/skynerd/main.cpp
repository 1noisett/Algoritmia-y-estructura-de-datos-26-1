#include <iostream>

#include "BibliotecaPilas/funcionesPila.h"
#include "BibliotecaPilas/Pila.h"
using namespace std;

#define FILCOL 7

int buscarCandidato(int red[][FILCOL],int candidato,int sig,int n) {
    if (sig>=n) return candidato; // ya se comparó con todos los servidores

    // Si el candidato NO envía paquetes al siguiente, el sig se convierte en
    // el nuevo candidato
    if (red[candidato][sig]==0) {
        return buscarCandidato(red,sig,sig+1,n);
    }else {// Si el candidato SÍ envía paquetes al sig, el sig se descarta
        return buscarCandidato(red,candidato,sig+1,n);
    }
}

bool verificarSkynerd(int red[][FILCOL], int candidato,int n) {
    // Columnas
    for (int i = 0; i < n; ++i) {
        if (i!=candidato) {
            if (red[i][candidato]!=0)
                return false;
        }
    }
    // Filas
    for (int i = 0; i < n; ++i) {
        if (i!=candidato) {
            if (red[candidato][i]==0)
                return false;
        }
    }
    return true;
}

int main() {
    int n = 7;
    int red[FILCOL][FILCOL] = {
        {  0,  0,  0,  0,  0,   0,  0},  // Servidor 1
        { 10,  0, 20, 30,  0,  20, 40},  // Servidor 2
        {  0,  0,  0,  0,  0, 100,  0},  // Servidor 3
        {  0,  0,  0,  0,  0,  80,  0},  // Servidor 4
        { 50, 10,  5, 10,  0, 100,  4},  // Servidor 5
        {100,  0,  0,  0,  0,   0,  0},  // Servidor 6
        {  0,  0,  0,  0,  0,   0,  0}   // Servidor 7
    };
    // Paso 1: Encontrar el candidato a SKYNERD recursivamente
    int candidato = buscarCandidato(red,0,1,n);
    // Paso 2: Verificar si el candidato realmente es SKYNERD
    if (verificarSkynerd(red,candidato,n)) {
        cout<<"Skynerd ha sido detectado en el servidor: "<< candidato+1<<endl;
    }else {
        cout<<"Skynerd no esta en la red"<<endl;
    }

    return 0;
}
