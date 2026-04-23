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

int main() {
    Lista listaTAD;
    construirLista(listaTAD);
    //Formación de los  jugadores
    string formacion[] = {"Defensa","Portero","Delantero","Mediocampo"};
    int cantidadPosiciones = size(formacion);

    int numCamiseta;
    string nombre;
    string posicion;
    ElementoLista jugador;
    ifstream input("jugadores.txt");
    while (input >> jugador.numCamiseta >> jugador.nombre >> jugador.posicion) {
        insertarFinal(listaTAD, jugador);
    }

    imprimirLista(listaTAD);
    cout<<endl<<endl<<endl;

    NodoLista *ptr = listaTAD.inicio;
    int cantidadJugadores = 0;
    while (ptr) {
        cantidadJugadores++;
        ptr = ptr->siguiente;
    }

    int j = 0;
    NodoLista *actual;
    NodoLista *anterior;
    NodoLista *ultimo;
    while (j<cantidadPosiciones) {
        actual = listaTAD.inicio;
        anterior = nullptr;
        // Buscamos el último nodo UNA VEZ al inicio del bucle de posiciones
        ultimo = obtenerUltimoNodo(listaTAD);
        for (int i = 0; i < cantidadJugadores; ++i) {
            if (actual->elemento.posicion == formacion[j]) {
                // 1. Guardamos el pase al siguiente nodo ANTES de desconectar
                NodoLista *nodoSig = actual->siguiente;
                NodoLista *nodoMover = actual;
                // 2. Desconectamos el nodo de su posición original
                if (anterior == nullptr) {
                    listaTAD.inicio = actual->siguiente;
                }else {
                    anterior->siguiente = actual->siguiente;
                }
                // 3. Lo mandamos al fondo de la lista
                nodoMover->siguiente = nullptr;
                ultimo->siguiente = nodoMover;
                // 4. Actualizamos quién es el nuevo último nodo
                ultimo = nodoMover;
                // 5. Avanzamos usando la copia de seguridad que guardamos
                actual = nodoSig;
            }else {
                // Solo avanzamos si no hubo que mover nada
                anterior = actual;
                actual = actual->siguiente;
            }
        }
        j++;
    }
    imprimirLista(listaTAD);

    return 0;
}
