#include <iostream>

#include "BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "BibliotecaArbolBinarioBusqueda/FuncionesArbolBinarioBusqueda.h"
using namespace std;

int main() {
    ArbolBinarioBusqueda arbol;
    construir(arbol);

    insertar(arbol,{4,'P'});
    insertar(arbol,{2,'U'});
    insertar(arbol,{1,'P'});
    insertar(arbol,{3,'C'});
    insertar(arbol,{6,'0'});
    insertar(arbol,{5,'2'});
    insertar(arbol,{7,'2'});
    insertar(arbol,{8,'4'});

    int n;
    // recorrerInOrder(arbol);
    cout<<"Ingrese número máximo de intentos: "; cin>>n;
    bool validacion;
    for (int i = 1; i <= n; ++i) {
        validacion = true;
        string contrasena;
        int tamanoContrasena;
        cout<<"Intento "<<i<<"/"<<n<<"."<<" Ingrese la contraseña: ";
        cin>>contrasena;
        tamanoContrasena = size(contrasena);
        int longArbol = numeroNodos(arbol);
        if (tamanoContrasena==longArbol) {
            for (int i = 0; i < tamanoContrasena; ++i) {
                ElementoArbolBinarioBusqueda e;
                e.caracter = contrasena[i];
                e.posicion = i+1;
                if (!buscar(arbol,e)) {
                    cout<<"Contraseña incorrecta. Intento fallido"<<endl;
                    validacion=false;
                    break;
                }
            }
            if (validacion) {
                cout<<"Acceso concedido"<<endl;
                break;
            }
        }else {
            cout<<"Longitud incorrecta. Intento fallido."<<endl;
            validacion=false;
        }
    }
    if (!validacion) cout<<"Se llegó al número de intentos fallidos permitidos"<<endl;
    destruirArbolBinario(arbol);
    return 0;
}
