#include <iostream>
using namespace std;

int contar(char *arr,int inicio,int fin, char polo) {
    if (inicio==fin) return arr[inicio]==polo ? 1 : 0;
    int medio = inicio + (fin-inicio)/2;

    int izq = contar(arr,inicio,medio,polo);
    int der = contar(arr,medio+1,fin,polo);
    return izq + der;
}

/*
 * la funcion encontarPoloMasFrecuente divide el arreglo en dos mitades.
 * cada mitad devuelve el polo mas frecuente de su propio rango
 * si ambos candidatos son iguales, ese es el resultado
 * si son distintos, vueves a contar ambos candidatos
 * devuelves el que tenga mayor frecuencia
 */
char encontrarPoloMasFrecuente(char *arr,int inicio,int fin) {
    if (inicio==fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;

    char poloIzq = encontrarPoloMasFrecuente(arr,inicio,medio);
    char poloDer = encontrarPoloMasFrecuente(arr,medio+1,fin);

    if (poloIzq==poloDer) return poloIzq;

    // contar en rango [inicio,fin]
    int contarIzq = contar(arr,inicio,fin,poloIzq);
    int contarDer = contar(arr,inicio,fin,poloDer);
    if (contarIzq>contarDer) {
        return poloIzq;
    }else {
        return poloDer;
    }
}

int main() {
    char arr[] = {'A','F','B','F','F','C','C','F'};
    int n = sizeof(arr)/sizeof(arr[0]);
    char poloMasFrec = encontrarPoloMasFrecuente(arr,0,n-1);
    cout<<poloMasFrec<<endl;
    cout<<contar(arr,0,n-1,poloMasFrec)<<endl;

    return 0;
}
