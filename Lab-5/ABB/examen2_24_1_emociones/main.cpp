#include <iostream>
#include "BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h"
#include "BibliotecaColas/Cola.h"
#include "BibliotecaColas/FuncionesCola.h"
using namespace std;

#define MAX_FIL 9
#define MAX_COL 3

bool pesoCorresponde(int peso, int emociones[][MAX_COL], int indEmocion) {
    for (int j = 0; j < MAX_COL; j++)
        if (emociones[indEmocion][j] == peso)
            return true;
    return false;
}

bool verificarEmociones(NodoArbolBinarioBusqueda *nodo,int emociones[][3],int combinaciones[][3],int fila,int count) {
    if (count==3) return true;
    if (esNodoVacio(nodo)) return false;

    int indEmocion = combinaciones[fila][count];
    if (pesoCorresponde(nodo->elemento.numero,emociones,indEmocion)) {
        return verificarEmociones(nodo->izq,emociones,combinaciones,fila,count+1) || verificarEmociones(nodo->der,emociones,combinaciones,fila,count+1);;
    }else{
        return false;
    }
}

void recorrerPorNiveles(ArbolBinarioBusqueda &arbol,int emociones[][3],int combinaciones[][3]) {
    Cola cola;
    construirCola(cola);
    int nivel = 0;
    if (!esArbolVacio(arbol)) {
        encolar(cola,arbol.raiz);
        while (!esColaVacia(cola)) {
            int nodosEnNivel = longitudCola(cola);
            int count = 0;
            for (int i = 0; i < nodosEnNivel; ++i) {
                NodoArbolBinarioBusqueda *nodo = desencolar(cola);

                // verificar combinación de emociones
                for (int i = 0; i < 3; ++i) {
                    bool cumple = verificarEmociones(nodo,emociones,combinaciones,i,0);
                    if (cumple) count++;
                }



                if (!esNodoVacio(nodo->izq)) encolar(cola,nodo->izq);
                if (!esNodoVacio(nodo->der)) encolar(cola,nodo->der);
            }
            cout<<"nivel "<<nivel+1<<" - "<<count<<" combinaciones"<<endl;

            nivel++;
        }
    }
}

int main() {
    ArbolBinarioBusqueda arbol;
    construir(arbol);
    insertar(arbol,{180});
    insertar(arbol,{120});
    insertar(arbol,{100});
    insertar(arbol,{150});
    insertar(arbol,{80});
    insertar(arbol,{140});
    insertar(arbol,{160});
    insertar(arbol,{90});
    insertar(arbol,{250});
    insertar(arbol,{230});
    insertar(arbol,{280});
    insertar(arbol,{200});
    insertar(arbol,{240});
    insertar(arbol,{260});

    int emociones[MAX_FIL][MAX_COL] = {
        {180,200,0},
        {140,230,80},
        {240,100,0},
        {280,0,0},
        {250,0,0},
        {260,120,0},
        {160,240,0},
        {120,80,0},
        {150,230,90}
    };
    int combinaciones[3][3] = {
        {5,8,1},
        {4,1,2},
        {2,7,8}
    };

    recorrerPorNiveles(arbol,emociones,combinaciones);
    return 0;
}
