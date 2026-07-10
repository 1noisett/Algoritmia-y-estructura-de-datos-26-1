#include <iostream>
using namespace std;

/*
 * Cuenta cuantas veces aparece un polo en arr[inicio,fin]
 * caso base: rango de un elemento, retorna 1 si coincide, 0 si no
 * division: punto medio del rango
 * conquista: se cuenta recursivamente en cada mitad
 * combinacion suma de ambos conteos
 */
int contar(char *arr,int inicio,int fin,char polo) {
    if (inicio==fin) return arr[inicio]==polo ? 1 : 0;
    int medio = inicio + (fin-inicio)/2;

    int izq = contar(arr,inicio,medio,polo);
    int der = contar(arr,medio+1,fin,polo);
    return izq+der;
}

/*
 * caso base: si el rango tiene 1 elemento, se retorna ese elemento
 * division: se calcula el punto medio del rango
 * conquista: se obtiene el polo candidato de cada mitad recursivamente
 * combinacion: si ambos candidatos coinciden, se retorna directamente
 * SI DIFIEREN, se cuenta cada candidato en el rango actual con contar()
 * y se retorna el de mayor frecuencia
 */

char encontrarPoloMasFrecuente(char *arr,int inicio,int fin) {
    if (inicio==fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;

    char poloIzq = encontrarPoloMasFrecuente(arr,inicio,medio);
    char poloDer = encontrarPoloMasFrecuente(arr,medio+1,fin);
    if (poloIzq==poloDer) return poloIzq; // si ambas mitades concuerdan, ese es el mayoritario

    // SI DIFIEREN, contamos cuál de los dos es más frecuente en el RANGO ACTUAL
    int contarIzq = contar(arr,inicio,fin,poloIzq);
    int contarDer = contar(arr,inicio,fin,poloDer);
    if (contarIzq>contarDer) {
        return poloIzq;
    }else {
        return poloDer;
    }
}

int main() {
    char almacen[] = {'A','F','B','F','F','C','C','F'};
    int n = 8;

    char polo = encontrarPoloMasFrecuente(almacen,0,n-1);
    int cantidad = contar(almacen,0,n-1,polo);

    cout<<"Polos con más unidades: "<<polo<<endl;
    cout<<"Cantidad de polo: "<<cantidad<<endl;
    return 0;
}

