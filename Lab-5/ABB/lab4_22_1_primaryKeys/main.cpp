#include <iostream>
#include "BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h"
using namespace std;

bool verificarInsercionRecursivo(NodoArbolBinarioBusqueda *nodo,const ElementoArbolBinarioBusqueda &e) {
    if (esNodoVacio(nodo)) {
        return true;
    }else {
        int cmp = comparaPK(nodo->elemento.campo1,nodo->elemento.campo2,e.campo1,e.campo2);
        if (cmp==1) {
            return verificarInsercionRecursivo(nodo->izq,e);
        }else if (cmp==-1) {
            return verificarInsercionRecursivo(nodo->der,e);
        }else {
            return false;
        }
    }
}

bool verificarInsercion(ArbolBinarioBusqueda &arbol,const ElementoArbolBinarioBusqueda &e) {
    if (verificarInsercionRecursivo(arbol.raiz,e)) {
        cout<<"Ok"<<endl; return true;
    }else {
        cout<<"Cannot insert duplicate key"<<endl; return false;
    }
}

bool verificarCamposPKRecursivo(NodoArbolBinarioBusqueda *nodo,const ElementoArbolBinarioBusqueda &pkActual,
                        const ElementoArbolBinarioBusqueda &pkNueva) {
    if (comparaPK(pkActual.campo1,pkActual.campo2,pkNueva.campo1,pkNueva.campo2)==0) {
        return true;
    }else if (verificarInsercionRecursivo(nodo,pkNueva)) {
        return true;
    }else {
        return false;
    }
}

bool verificarCamposPK(ArbolBinarioBusqueda &arbol,const ElementoArbolBinarioBusqueda &pkActual,
                        const ElementoArbolBinarioBusqueda &pkNueva) {
    if (verificarCamposPKRecursivo(arbol.raiz,pkActual,pkNueva)) {
        cout<<"Ok"<<endl;
        return true;
    }else {
        cout<<"Violation of Primary Key constraint on update"<<endl;
        return false;
    }
}

NodoArbolBinarioBusqueda *buscarNodoPK(NodoArbolBinarioBusqueda *nodo,const ElementoArbolBinarioBusqueda &e) {
    if (esNodoVacio(nodo)) return nullptr;
    int cmp = comparaPK(nodo->elemento.campo1,nodo->elemento.campo2,e.campo1,e.campo2);
    if (cmp==1)  return buscarNodoPK(nodo->izq,e);
    if (cmp==-1) return buscarNodoPK(nodo->der,e);
    return nodo;
}

void actualizarCampos(ArbolBinarioBusqueda &arbol,const ElementoArbolBinarioBusqueda &pkActual,
                        const ElementoArbolBinarioBusqueda &nuevo) {
    if (!verificarCamposPK(arbol,pkActual,nuevo)) // imprime el resultado de la validacion (item b)
        return;
    if (comparaPK(pkActual.campo1,pkActual.campo2,nuevo.campo1,nuevo.campo2)==0) {
        // PK intacta: solo cambia campo3, se modifica en el sitio sin tocar la estructura
        NodoArbolBinarioBusqueda *nodo = buscarNodoPK(arbol.raiz,pkActual);
        if (!esNodoVacio(nodo))
            nodo->elemento.campo3 = nuevo.campo3;
    }else {
        // PK cambia: el registro debe reubicarse segun la nueva PK
        eliminar(arbol,pkActual);
        insertar(arbol,nuevo);
    }
}

int main() {
    ArbolBinarioBusqueda arbol;
    construir(arbol);

    insertar(arbol,{10,8,5});
    insertar(arbol,{8,20,6});
    insertar(arbol,{5,10,3});
    insertar(arbol,{10,1,7});
    insertar(arbol,{15,10,3});
    insertar(arbol,{16,8,7});

    // verificarInsercion(arbol,{5,11,6});
    // verificarCamposPK(arbol,{5,10,3},{15,10,3});

    cout<<"Arbol inicial:     "; recorrerPreOrder(arbol); cout<<endl;

    // solo cambia campo3: (5 10 3) -> (5 10 9), el nodo no se mueve
    actualizarCampos(arbol,{5,10,3},{5,10,9});
    cout<<"Tras campo3 -> 9:  "; recorrerPreOrder(arbol); cout<<endl;

    // cambia la PK a una libre: (5 10 9) -> (5 11 9), el nodo se reubica
    actualizarCampos(arbol,{5,10,9},{5,11,9});
    cout<<"Tras PK -> (5,11): "; recorrerPreOrder(arbol); cout<<endl;

    // violacion: (16 8 7) no puede tomar la PK (15,10), ya existe
    actualizarCampos(arbol,{16,8,7},{15,10,7});
    cout<<"Tras violacion:    "; recorrerPreOrder(arbol); cout<<endl;

    return 0;
}