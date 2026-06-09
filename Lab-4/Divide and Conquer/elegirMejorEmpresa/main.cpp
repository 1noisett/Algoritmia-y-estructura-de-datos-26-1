#include <iostream>
using namespace std;

#define N 10

// se parte el rango en dos mitades y se obtiene el maximo de cada una recursivamente
int mayorCantidadProd(int *arr,int inicio,int fin) {
    if (inicio==fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;
    int maxIzq = mayorCantidadProd(arr,inicio,medio);
    int maxDer = mayorCantidadProd(arr,medio+1,fin);
    return (maxIzq>maxDer) ? maxIzq : maxDer; // combinar
}

int contarHorasPico(int *arr,int inicio,int fin,int maximo) {
    if (inicio==fin) return (arr[inicio]==maximo) ? 1 : 0;
    int medio = inicio + (fin-inicio)/2;
    int izq = contarHorasPico(arr,inicio,medio,maximo);
    int der = contarHorasPico(arr,medio+1,fin,maximo);
    return izq+der;
}

int elegirMejorEmpresa(int empresas[][N],int inicio,int fin) {
    if (inicio==fin) return inicio;

    int medio = inicio + (fin-inicio)/2;

    // evaluar la mejor empresa de la mitad izquierda y derecha
    int indIzq = elegirMejorEmpresa(empresas,inicio,medio);
    int indDer = elegirMejorEmpresa(empresas,medio+1,fin);

    // calcular el máximo y las horas pico para la empresa ganadora de la izquierda
    int maxIzq = mayorCantidadProd(empresas[indIzq],0,N-1);
    int picosIzq = contarHorasPico(empresas[indIzq],0,N-1,maxIzq);

    // calcular el máximo y las horas pico para la empresa ganadora de la derecha
    int maxDer = mayorCantidadProd(empresas[indDer],0,N-1);
    int picosDer = contarHorasPico(empresas[indDer],0,N-1,maxDer);

    // retornar la empresa que tenga menor cantidad de horas pico
    return (picosIzq<=picosDer) ? indIzq : indDer;
}

int main() {
    // Etiquetas de hora, solo para mostrar un resultado legible.
    string etiquetaHora[N] = {"2pm","3pm","4pm","5pm","6pm","7pm","8pm","9pm","10pm","11pm"};
    int empresas[3][N] = {
        {15, 12, 10, 17, 15, 18, 18, 18, 12, 16}, // Empresa 1
        {14, 17, 17, 17, 17, 12, 14, 14, 12, 12}, // Empresa 2
        {16, 18, 20, 20, 15, 18, 16, 18, 18, 16}  // Empresa 3
    };

    for (int i = 0; i < 3; ++i)
        cout << mayorCantidadProd(empresas[i], 0, N - 1) << endl;

    int mejorEmpresa = elegirMejorEmpresa(empresas,0,2);
    cout << "El maestro Splinter debe realizar el pedido en la Empresa " << mejorEmpresa + 1 << endl;

    return 0;
}
