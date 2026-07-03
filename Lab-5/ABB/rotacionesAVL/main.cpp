/*
 * Estrategia: se usa un ABB autobalanceado (AVL) donde cada nodo guarda su altura.
 * Al insertar, se desciende como en un ABB normal y, de regreso de la recursion,
 * se actualiza la altura de cada nodo y se calcula su factor de balance (FB).
 * Si FB sale del rango [-1,1] se aplica la rotacion correspondiente (LL, RR, LR o RL)
 * para restaurar el balance sin alterar el orden del arbol.
 */
#include <iostream>
#include "BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h"
using namespace std;

int main() {
    ArbolBinarioBusqueda arbol;
    construir(arbol);

    int dnis[] = {72649318, 50823147, 81234567, 40987654, 65012345, 94561237, 30124598};
    int cantidad = 7;

    cout<<"Insertando valores en el AVL:"<<endl;
    for (int i = 0; i < cantidad; ++i) {
        cout<<"Insertar "<<dnis[i]<<endl;
        insertarAVL(arbol,dnis[i]);
    }

    cout<<endl<<"Recorrido inorden del AVL (clave y altura):"<<endl;
    recorrerInOrder(arbol);
    cout<<endl;

    return 0;
}
