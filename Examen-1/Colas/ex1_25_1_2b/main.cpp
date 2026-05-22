#include <iostream>

#include "BibliotecaColas/Cola.h"
#include "BibliotecaColas/FuncionesCola.h"
using namespace std;

struct Monitoreo {
    Cola colaTemperaturas;
    int k;
    int n;
    double sumaAcumulada;
};

void inicializar(Monitoreo &m, int k) {
    construirCola(m.colaTemperaturas);
    m.k = k;
    m.n = 0;
    m.sumaAcumulada = 0;
}

void agregarTemperatura(Monitoreo &m, int temp) {
    ElementoCola e;
    e.dato = temp;
    if (m.n < m.k) {
        encolar(m.colaTemperaturas,e);
        m.sumaAcumulada += temp;
        m.n++;
    }else {
        m.sumaAcumulada -= desencolar(m.colaTemperaturas).dato;
        encolar(m.colaTemperaturas,e);
        m.sumaAcumulada += temp;
    }
}

double calcularPromedio(Monitoreo &m) {
    return m.sumaAcumulada/m.n;
}

int main() {
    int k;
    cout<<"Ingrese k: ";
    cin>>k;

    Monitoreo m;
    inicializar(m,k);

    int temp;
    while (true) {
        cout<<"Ingrese temperatura: "; cin>>temp;
        if (temp==-1) break;
        agregarTemperatura(m,temp);
        cout<<"Promedio: "<<calcularPromedio(m)<<endl;
    }

    return 0;
}
