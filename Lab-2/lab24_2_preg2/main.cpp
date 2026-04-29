#include <iostream>
#include <fstream>
#include "BibliotecaFunciones/lista.h"
#include "BibliotecaFunciones/listaFunciones.h"

using namespace std;

void cargarDatosLista(Lista &listaTAD) {
    char complejidad,c,id[10];
    int disPersonal,esHoraPunta,velPromedio = 45;
    double distancia;
    ElementoLista pedido;
    ifstream input("pedidos.txt");
    while (true) {
        input.getline(id,10,',');
        if (input.eof()) break;
        strcpy(pedido.id,id);
        input>>complejidad>>c>>disPersonal>>c>>distancia>>c>>esHoraPunta;
        input.get();
        if (complejidad=='b')
            pedido.tiempoPreparacion = 10;
        else if (complejidad=='m')
            pedido.tiempoPreparacion = 20;
        else
            pedido.tiempoPreparacion = 30;
        if (disPersonal==0) pedido.tiempoPreparacion += 5;
        pedido.tiempoEstimadoViaje = distancia/velPromedio*60;
        if (esHoraPunta==1) pedido.tiempoEstimadoViaje += 10;
        insertarFinal(listaTAD,pedido);
    }
}

void ordenarLista(Lista &listaTAD) {

    for (int pasada = 1; pasada<=2 ; ++pasada) {
        // 1. CREAR LAS 10 CUBETAS (10 LISTAS AUXILIARES)
        Lista cubetas[10];
        for (int i = 0; i < 10; ++i) {
            construirLista(cubetas[i]);
        }

        // 2. CREAR EL PRIMER NODO Y VACIAR LA LISTA ORIGINAL
        NodoLista *actual = listaTAD.inicio;
        listaTAD.inicio = nullptr;
        // 3. DISTRIBUCIÓN
        while (actual) {
            // Guardar siguiente y aislar nodo actual
            NodoLista *nodoSig = actual->siguiente;
            actual->siguiente = nullptr;
            // Obtener el tiempo total
            int tiempoTotal = actual->elemento.tiempoPreparacion + actual->elemento.tiempoEstimadoViaje;
            int digito;
            // Lógica para extraer el dígito
            if (pasada==1) {
                digito = tiempoTotal%10;        // Unidades
            }else {
                digito = (tiempoTotal/10)%10;   // Decenas
            }
            // Enlazar el nodo actual en la cubeta correspondiente
            if (cubetas[digito].inicio == nullptr) {
                cubetas[digito].inicio = actual;
            }else {
                NodoLista *ultimo = obtenerUltimoNodo(cubetas[digito]);
                ultimo->siguiente = actual;
            }
            actual = nodoSig;
        }
        // 4. REENSAMBLAJE
        for (int i = 0; i < 10; ++i) {
            if (cubetas[i].inicio != nullptr) {
                if (listaTAD.inicio == nullptr) {
                    listaTAD.inicio = cubetas[i].inicio;
                }else {
                    NodoLista *ultimo = obtenerUltimoNodo(listaTAD);
                    ultimo->siguiente = cubetas[i].inicio;
                }
            }
        }
    }
}

int main() {
    Lista listaTAD;
    construirLista(listaTAD);
    // Cargar los datos a la lista
    cargarDatosLista(listaTAD);
    // Imprimir la lista
    imprimirLista(listaTAD);
    // Ordenar la lista
    ordenarLista(listaTAD);
    // Imprimir lista ordenada
    cout<<"\n\n";
    imprimirLista(listaTAD);
    return 0;
}
