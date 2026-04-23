#include <iostream>
#include "listaFunciones.h"
using namespace std;

int main() {
    Lista listaTAD;
    construirLista(listaTAD);
    cout << "La lista esta vacía: " << (esListaVacia(listaTAD) ? "Sí" : "No") << endl;

    //Insertar al inicio
    // for (int i = 0; i < 18; i+= 3) {
    //     ElementoLista numm;
    //     numm.dato = i;
    //     insertarInicio(listaTAD,numm);
    // }

    //Insetar al final
    // for (int i = 0; i < 18; i+= 3) {
    //     ElementoLista numm;
    //     numm.dato = i;
    //     insertarFinal(listaTAD,numm);
    // }

    //Insertar en orden
    // srand(time(nullptr));
    // for (int i = 0; i < 18; i++) {
    //     ElementoLista numm;
    //     numm.dato = rand() % 50;
    //     insertarEnOrden(listaTAD,numm);
    // }
    ElementoLista elemento;
    elemento.dato = 3;
    insertarEnOrden(listaTAD,elemento);
    elemento.dato = 10;
    insertarEnOrden(listaTAD,elemento);
    elemento.dato = 7;
    insertarEnOrden(listaTAD,elemento);
    elemento.dato = 5;
    insertarEnOrden(listaTAD,elemento);
    elemento.dato = 2;
    insertarEnOrden(listaTAD,elemento);
    //Eliminar un nodo en específico
    imprimirLista(listaTAD);
    elemento.dato = 7;
    eliminarNodo(listaTAD,elemento);
    cout<<endl<<endl;
    //Imprimir lista
    imprimirLista(listaTAD);
    //Eliminar la lista
    eliminarLista(listaTAD);
    return 0;
}
