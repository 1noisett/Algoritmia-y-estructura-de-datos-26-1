#include <iostream>

#include "BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h"
#include "BibliotecaPilas/funcionesPila.h"
#include "BibliotecaPilas/Pila.h"
using namespace std;

void insertarRecursivo(NodoArbolBinarioBusqueda *&nodo,const ElementoArbolBinarioBusqueda &elemento) {
    if (esNodoVacio(nodo)) {
        plantarNodoArbolBinario(nodo,nullptr,elemento,nullptr);
    }else {
        int cmp = comparaElementos(nodo->elemento.idServidor,elemento.idServidor);
        if (cmp==1) {
            insertarRecursivo(nodo->izq,elemento);
        }else if (cmp==-1) {
            insertarRecursivo(nodo->der,elemento);
        }else {
            cout<<"nodo ya existe"<<endl;
        }
    }
}

void insertar(ArbolBinarioBusqueda &arbol,const ElementoArbolBinarioBusqueda &elemento) {
    insertarRecursivo(arbol.raiz,elemento);
}

NodoArbolBinarioBusqueda * recorrerPreOrden(ArbolBinarioBusqueda &arbol) {
    // Estrategia: recorrido preorden ITERATIVO con pila explícita.
    // Se imprime cada nodo al desapilarlo. Si es SkyNerd ('S') se corta
    // el recorrido ANTES de apilar a sus hijos, de modo que nunca se
    // visitan los servidores que lo defienden.
    Pila pila;
    construirPila(pila);

    apilar(pila, arbol.raiz);          // arranca con la raíz
    NodoArbolBinarioBusqueda *nodo = nullptr;
    while (!esPilaVacia(pila)) {
        nodo = desapilar(pila);
        imprimirNodo(nodo);            // preorden: imprimo al sacar

        if (nodo->elemento.flag == 'S') break;   // encontré SkyNerd → paro

        // apilo DER primero y IZQ después: como la pila es LIFO,
        // la IZQ queda arriba y se procesa antes (orden preorden)
        if (nodo->der) apilar(pila, nodo->der);
        if (nodo->izq) apilar(pila, nodo->izq);
    }
    return nodo;
}

void recorrerInOrden(ArbolBinarioBusqueda &arbol) {
    // Estrategia: inorden iterativo. Bajo apilando todo lo de la izquierda;
    // al no poder bajar más, desapilo (ese es el menor pendiente), lo imprimo,
    // y me muevo a su subárbol derecho para repetir.
    Pila pila;
    construirPila(pila);
    NodoArbolBinarioBusqueda *actual = arbol.raiz;

    while (actual || !esPilaVacia(pila)) {
        while (actual) {                  // bajo a la izquierda apilando
            apilar(pila, actual);
            actual = actual->izq;
        }
        actual = desapilar(pila);         // el más a la izquierda pendiente
        imprimirNodo(actual);             // imprimo en medio
        actual = actual->der;             // ahora voy a su derecha
    }
}

void recorrerPostOrden(ArbolBinarioBusqueda &arbol) {
    // Estrategia: postorden iterativo con DOS pilas. En p1 hago un recorrido
    // tipo "raíz-der-izq" y voy volcando a p2. Al final, p2 contiene los nodos
    // en orden raíz-der-izq invertido = izq-der-raíz = postorden. Solo imprimo p2.
    Pila p1, p2;
    construirPila(p1);
    construirPila(p2);

    apilar(p1, arbol.raiz);
    while (!esPilaVacia(p1)) {
        NodoArbolBinarioBusqueda *nodo = desapilar(p1);
        apilar(p2, nodo);                 // vuelco a p2
        if (nodo->izq) apilar(p1, nodo->izq);   // izq primero
        if (nodo->der) apilar(p1, nodo->der);   // der después (sale antes)
    }
    while (!esPilaVacia(p2)) {
        imprimirNodo(desapilar(p2));      // p2 ya está en orden postorden
    }
}

void eliminarHijosSkynerd(NodoArbolBinarioBusqueda *skynerd) {
    if (esNodoVacio(skynerd)) return;

    Pila p1, p2;
    construirPila(p1);
    construirPila(p2);

    // Apilo los dos hijos de SkyNerd (izq primero, der despues).
    // SkyNerd no entra: solo se elimina la red que lo defiende.
    if (skynerd->izq) apilar(p1, skynerd->izq);
    if (skynerd->der) apilar(p1, skynerd->der);

    // FASE 1 - Recoleccion: recorro raiz-der-izq volcando a p2.
    while (!esPilaVacia(p1)) {
        NodoArbolBinarioBusqueda *nodo = desapilar(p1);
        apilar(p2, nodo);
        if (nodo->izq) apilar(p1, nodo->izq);
        if (nodo->der) apilar(p1, nodo->der);
    }

    // FASE 2 - Borrado: p2 entrega los nodos en postorden (hijo antes que padre).
    // Aqui ya no se leen punteros ->izq/->der, por lo que borrar es seguro.
    while (!esPilaVacia(p2)) {
        NodoArbolBinarioBusqueda *nodo = desapilar(p2);
        imprimirNodo(nodo);                    // muestro que servidor se elimina
        delete nodo;                           // libero la memoria del nodo
    }

    // SkyNerd queda sin defensa: anulo sus punteros para evitar referencias
    // colgantes hacia memoria ya liberada.
    skynerd->izq = nullptr;
    skynerd->der = nullptr;
}

void  rrecorrerPreOrden(ArbolBinarioBusqueda &abb) {

}

int main() {
    ArbolBinarioBusqueda abb;
    construir(abb);
    // insertar nodos
    insertar(abb,{'N',100});
    insertar(abb,{'N',50});
    insertar(abb,{'N',25});
    insertar(abb,{'N',75});
    insertar(abb,{'N',150});
    insertar(abb,{'N',175});
    insertar(abb,{'S',125});
    insertar(abb,{'N',200});
    insertar(abb,{'N',110});
    insertar(abb,{'N',140});
    insertar(abb,{'N',105});
    insertar(abb,{'N',115});
    insertar(abb,{'N',130});

    NodoArbolBinarioBusqueda *skynerd = nullptr;
    cout << "Ubicando a SkyNerd:" << endl;
    skynerd = recorrerPreOrden(abb);

    cout << endl << endl;

    cout << "Eliminando el subarbol que lo defiende:" << endl;
    eliminarHijosSkynerd(skynerd);

    cout << endl;
    return 0;
}