#include <iostream>
#include "BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h"

using namespace std;

// buscar, eliminar, insertas --->>> ABB

int main() {

    ArbolBinarioBusqueda arbol;
    construir(arbol);

    insertar(arbol,{100});
    insertar(arbol,{50});
    insertar(arbol,{150});
    insertar(arbol,{125});
    insertar(arbol,{175});
    insertar(arbol,{200});
    insertar(arbol,{25});
    insertar(arbol,{75});

    cout<<"Recorrer In Order: "<<endl;
    recorrerInOrder(arbol); cout<<endl;

    cout<<"Recorrer Pre Order: "<<endl;
    recorrerPreOrder(arbol); cout<<endl;

    cout<<"Recorrer Post Order: "<<endl;
    recorrerPostOrder(arbol); cout<<endl;

    // Función de búsqueda
    cout<<endl<<"Se encuentra 125 en arbol: "<<buscar(arbol, {125})<<endl;

    eliminar(arbol, {175});
    eliminar(arbol, {25});
    eliminar(arbol, {150});
    eliminar(arbol, {100});

    cout << "Recorrer In Order despues del borrado: " << endl;
    //     50   75  125  200
    recorrerInOrder(arbol); cout<<endl;

    destruirArbolBinario(arbol);

    return 0;
}
