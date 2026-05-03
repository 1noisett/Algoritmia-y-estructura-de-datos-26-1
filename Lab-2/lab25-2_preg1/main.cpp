#include <fstream>
#include <iostream>

#include "BibliotecaFunciones/listaFunciones.h"
using namespace std;

#include "BibliotecaFunciones/lista.h"

/*
7 Martínez Delantero
1 Ramírez Portero
5 Pérez Defensa
8 Torres Mediocampo
9 López Delantero
3 Gómez Defensa
7 Miguel Delantero
99 Kevin Portero
*/

void reordenaFormacion(Lista &listaTAD,string formacion[],int cantidadPosiciones){
    NodoLista *nuevaCabeza = nullptr;
    NodoLista *nuevaCola = nullptr;
    // Iteramos sobre las posiciones que pide el entrenador
    for (int p = 0; p < cantidadPosiciones; ++p) {
        NodoLista *actual = listaTAD.inicio;
        NodoLista *anterior = nullptr;
        // Recorremos los jugadores de la lista original
        while (actual) {
            if (actual->elemento.posicion == formacion[p]) {
                NodoLista *nodoSig = actual->siguiente;
                if (anterior==nullptr) {
                    listaTAD.inicio = actual->siguiente;
                }else {
                    anterior->siguiente = actual->siguiente;
                }
                // Convertimos actual a un nodo independiente
                actual->siguiente = nullptr;
                if (nuevaCabeza==nullptr) {
                    nuevaCabeza = nuevaCola = actual;
                }else {
                    nuevaCola->siguiente = actual;
                    nuevaCola = actual;
                }
                // Avanzamos usando la copia de seguridad
                actual = nodoSig;
            }else {
                anterior = actual;
                actual = actual->siguiente;
            }
        }
    }
    // El paso final
    listaTAD.inicio = nuevaCabeza;
}

int main() {
    Lista listaTAD;
    construirLista(listaTAD);
    //Formación de los  jugadores
    string formacion[] = {"Defensa","Portero","Delantero","Mediocampo","Carrilero"};
    int cantidadPosiciones = size(formacion);
    //Elemento jugador
    int numCamiseta;
    string nombre;
    string posicion;
    ElementoLista jugador;
    ifstream input("jugadores.txt");
    while (input >> jugador.numCamiseta >> jugador.nombre >> jugador.posicion) {
        insertarFinal(listaTAD, jugador);
    }
    //Imprimir lista jugadores
    imprimirLista(listaTAD);
    cout<<"\n\n\n";
    //Reordenar los jugadores
    reordenaFormacion(listaTAD,formacion,cantidadPosiciones);
    //Imprimir la lista ordenada de jugadores
    imprimirLista(listaTAD);

    return 0;
}
