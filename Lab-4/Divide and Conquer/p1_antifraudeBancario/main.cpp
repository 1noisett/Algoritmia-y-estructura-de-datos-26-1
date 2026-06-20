#include <iostream>
using namespace std;

int indMontoExacto(int *arr,int inicio,int fin,int montoExacto) {
    if (inicio==fin) {
        if (arr[inicio]==montoExacto) {
            return inicio;
        }else {
            return -1;
        }
    }

    int medio = inicio + (fin-inicio)/2;
    if (arr[medio]<montoExacto) {
        return indMontoExacto(arr,medio+1,fin,montoExacto);
    }else {
        return indMontoExacto(arr,inicio,medio,montoExacto);
    }
}

int encontrarPrimerMontoMayor(int *arr,int inicio,int fin,int umbral) {
    if (inicio==fin) {
        if (arr[inicio]>umbral)
            return inicio;
        else
            return -1;
    }
    int medio = inicio + (fin-inicio)/2;

    if (arr[medio]<=umbral) {
        return encontrarPrimerMontoMayor(arr,medio+1,fin,umbral);
    }else {
        return encontrarPrimerMontoMayor(arr,inicio,medio,umbral);
    }
}

int main() {
    int montos[] = {12, 30, 45, 45, 80, 110, 150, 150, 220, 300, 480, 900};
    int n = sizeof(montos) / sizeof(montos[0]);
    int U = 150;   // umbral
    int M = 45;    // monto a verificar
    int indicePrimerMontoMayor= encontrarPrimerMontoMayor(montos,0,n-1,U);
    int indiceMontoExacto = indMontoExacto(montos,0,n-1,M);
    if (indicePrimerMontoMayor==-1) cout<<"0 transacciones sospechosas"<<endl;
    else cout<<indicePrimerMontoMayor<<"  "<<n-indicePrimerMontoMayor<<endl;
    if (indiceMontoExacto==-1) cout<<"No registrado"<<endl;
    else cout<<"Sí registrado"<<endl;
    return 0;
}
