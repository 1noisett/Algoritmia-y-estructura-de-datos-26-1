#include <iostream>
#include <fstream>
#include "BibliotecaFunciones/lista.h"
#include "BibliotecaFunciones/listaFunciones.h"
using namespace std;
// Con & trabajo con un alias de la variable original
// Con * paso la dirección de memoria y uso ->. En ambos no hay copia y modifico el original

void reordenarLista(Lista &listaTAD,int n,int k) {
    if (n==k) return;
    if (n > k) {
        // Intercambias los números n y k
        int tempPos = n; n = k; k = tempPos;
    }
    //Creamos los dos nodos
    NodoLista *nodoN = nullptr, *prevN = nullptr;
    NodoLista *nodoK = nullptr, *prevK = nullptr;
    //Buscamos su posicion actual y anterior
    NodoLista *actual = listaTAD.inicio;
    NodoLista *previo = nullptr;
    int i = 1;
    while (actual && i <= k) {
        if (i == n) {
            // ¡Llegamos a la primera parada! Guardamos los datos de N
            nodoN = actual;
            prevN = previo;
        }
        if (i == k) {
            // ¡Llegamos al final! Guardamos los datos de K
            nodoK = actual;
            prevK = previo;
        }
        // Avanzamos el tren
        previo = actual;
        actual = actual->siguiente;
        i++;
    }
    //Logica
    if (nodoN->siguiente == nodoK) {
        if (prevN==nullptr) listaTAD.inicio = nodoK;
        else prevN->siguiente = nodoK;

        nodoN->siguiente = nodoK->siguiente;
        nodoK->siguiente = nodoN;
    }else {
        if (prevN==nullptr) {
            listaTAD.inicio = nodoK;
            NodoLista *sigK = nodoK->siguiente;
            nodoK->siguiente = nodoN->siguiente;
            prevK->siguiente = nodoN;
            nodoN->siguiente = sigK;
        }else {
            NodoLista *sigK = nodoK->siguiente;
            prevN->siguiente = nodoK;
            nodoK->siguiente = nodoN->siguiente;
            prevK->siguiente = nodoN;
            nodoN->siguiente = sigK;
        }
    }
}


int main() {
    Lista listaTAD;
    construirLista(listaTAD);
    ifstream input("libros.txt");
    char codLibro[10],nombre[40],c;
    while (true) {
        ElementoLista elemento;
        input.getline(codLibro,10,'-');
        if (input.eof()) break;
        input.getline(nombre,40,'-');
        input>>elemento.unidadesVendidas>>c>>elemento.cantidadLikes;
        input.get();
        strcpy(elemento.codigoLibro,codLibro);
        strcpy(elemento.nombre,nombre);
        insertarFinal(listaTAD,elemento);
    }
    imprimirLista(listaTAD);

    //Reordenamiento. Mayor cantidad de likes intercambiar con menor cantidad de likes
    //Libro con más unidades vendidas intercambiar con menos unidades vendidas
    NodoLista *actual = listaTAD.inicio;
    // Variables para Likes
    int maxCantLikes = -1, posMaxLikes = -1;
    int minCantLikes = 999999, posMinLikes = -1;
    // Variables para Ventas
    int maxVentas = -1, posMaxVentas = -1;
    int minVentas = 999999, posMinVentas = -1;

    int posicion = 1;
    while (actual) {
        // Analizamos Likes
        int likes = actual->elemento.cantidadLikes;
        if (likes > maxCantLikes) { maxCantLikes = likes; posMaxLikes = posicion; }
        if (likes < minCantLikes) { minCantLikes = likes; posMinLikes = posicion; }

        // Analizamos Ventas
        int ventas = actual->elemento.unidadesVendidas;
        if (ventas > maxVentas) { maxVentas = ventas; posMaxVentas = posicion; }
        if (ventas < minVentas) { minVentas = ventas; posMinVentas = posicion; }

        posicion++;
        actual = actual->siguiente;
    }
    cout << maxCantLikes << "   " << posMaxLikes << "   "
     << minCantLikes << "   " << posMinLikes << endl;

    cout << maxVentas << "   " << posMaxVentas << "   "
         << minVentas << "   " << posMinVentas << endl;

    reordenarLista(listaTAD,posMaxLikes,posMinLikes);
    reordenarLista(listaTAD,posMaxVentas,posMinVentas);
    cout<<"\n\n";
    imprimirLista(listaTAD);



    //invertir lista recursivo
    //Fusionar lista
    return 0;
}
