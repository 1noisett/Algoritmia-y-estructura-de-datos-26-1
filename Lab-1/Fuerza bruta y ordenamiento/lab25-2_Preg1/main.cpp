#include <iostream>
using namespace std;

struct Recurso {
    int id;
    int costo;
    int beneficio;
    int falsosNegativos;
};

void crearCromosoma(int *cromosoma, int tamano, int combinacion) {
    for (int i = 0; i < tamano; i++) {
        cromosoma[i] = combinacion % 2;
        combinacion = combinacion / 2;
    }
}

int main() {
    Recurso lista[8] = {
        {1,35000,80,1},
        {2,24000,60,3},
        {3,30000,70,2},
        {4,27000,48,1},
        {5,10000,20,1},
        {6,7000,35,2},
        {7,6000,10,1},
        {8,40000,40,3}
    };
    //Crear cromosoma
    int tamano = 8;
    int *cromosoma = new int[tamano];
    int combinaciones = 1 << tamano;

    int presupuesto = 100000;
    int beneficioTotalComp = 190;
    int falsosNegativosComp = 4;
    for (int i = 0; i < combinaciones; i++) {
        crearCromosoma(cromosoma,tamano,i);
        int costoTotal = 0;
        int beneficioTotal = 0;
        int falsosNegativos = 0;
        for (int j = 0; j < tamano; j++) {
            costoTotal += lista[j].costo * cromosoma[j];
            beneficioTotal += lista[j].beneficio * cromosoma[j];
            falsosNegativos += lista[j].falsosNegativos * cromosoma[j];
        }
        //Filtros según el problema
        if (costoTotal <= presupuesto and beneficioTotal>=beneficioTotalComp and falsosNegativos<=falsosNegativosComp) {
            cout<<"Recursos: {";
            for (int j = 0; j<tamano; j++) {
                if (cromosoma[j]==1)
                    cout<<lista[j].id<<" ";
            }
            cout<<"}, Costo total: "<<costoTotal<<", Beneficio: "<<beneficioTotal<<", Falsos negativos: "<<falsosNegativos<<endl;

        }
    }
    return 0;
}