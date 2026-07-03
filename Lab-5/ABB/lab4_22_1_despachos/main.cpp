#include <iostream>
#include "BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h"
using namespace std;

void despachar(ArbolBinarioBusqueda &arbol,int solicitado) {
    while (solicitado>0 && !esArbolVacio(arbol)) {
        NodoArbolBinarioBusqueda *nodo = minimoArbol(arbol.raiz);
        if (nodo->elemento.cantProds>solicitado) {
            nodo->elemento.cantProds -= solicitado;
            solicitado = 0;
        }else {
            solicitado -= nodo->elemento.cantProds;
            eliminar(arbol,nodo->elemento);
        }
    }
    if (solicitado>0) {
        cout<<"No se logro despachar: "<<solicitado<<" productos"<<endl;
    }
}

int main() {
    ArbolBinarioBusqueda arbol;
    construir(arbol);

    insertar(arbol,{20220815,40});
    insertar(arbol,{20220710,50});
    insertar(arbol,{20220930,30});
    insertar(arbol,{20220630,50});
    insertar(arbol,{20220720,50});
    insertar(arbol,{20220624,40});
    insertar(arbol,{20220615,40});
    insertar(arbol,{20220618,40});

    cout<<"La representacion, en preorden, del arbol de lotes de productos es:"<<endl;
    recorrerPreOrder(arbol); cout<<endl;

    int cantidadSolic;
    cout<<"Ingrese la cantidad de solicitudes de despacho: "; cin>>cantidadSolic;
    for (int i = 0; i < cantidadSolic; ++i) {
        int solicitado;
        cout<<"Ingrese la cantidad de unidades para el despacho "<<i+1<<": "; cin>>solicitado;
        despachar(arbol,solicitado);
        cout<<"La representacion, en preorden, del arbol de lotes de productos luego del despacho "<<i+1<<" es:"<<endl;
        recorrerPreOrder(arbol); cout<<endl;
    }

    return 0;
}
