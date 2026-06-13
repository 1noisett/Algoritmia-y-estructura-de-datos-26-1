#include <iostream>
#include <fstream>
using namespace std;

#define N 30

int obtenerMenorNumero(int *arr,int inicio,int fin) {
    if (inicio==fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;

    int izq = obtenerMenorNumero(arr,inicio,medio);
    int der = obtenerMenorNumero(arr,medio+1,fin);
    return (izq<=der) ? izq : der;
}

int max3(int maxIzq,int maxDer,int cruce) {
    int m = (maxIzq>maxDer) ? maxIzq : maxDer;
    return (cruce>m) ? cruce : m;
}

int maxSubArrayCruce(int *arr,int inicio,int medio,int fin,int pesoMenor,int &iniCruce, int &finCruce) {
    int diasMinIzq = 0;
    for (int i = medio; i>=inicio; --i) {
        if (arr[i]==pesoMenor) diasMinIzq++;
        else break;
    }

    int diasMinDer = 0;
    for (int i = medio+1; i<=fin; ++i) {
        if (arr[i]==pesoMenor) diasMinDer++;
        else break;
    }

    // el rango sale gratis de los propios contadores
    // el bloque que toca el medio arranca diasMinIzq posiciones antes de medio
    // y termina diasMinDer posiciones después de medio.
    iniCruce = medio - diasMinIzq + 1; // + 1 porque diasMinIzq incluye al propio medio
    finCruce = medio + diasMinDer;


    return diasMinIzq + diasMinDer;
}

int cantDiasMenorPeso(int *arr,int inicio,int fin,int pesoMenor,int &iniMejor,int &finMejor) {
    if (inicio==fin) {
        if (arr[inicio]==pesoMenor) {
            iniMejor = inicio; // el bloque es este unico día: rango [inicio, inicio]
            finMejor = inicio;
            return 1;
        }else {
            iniMejor = -1;
            finMejor = -1;
            return 0;
        }
    }
    int medio = inicio + (fin-inicio)/2;

    int iniIzq, finIzq, iniDer, finDer, iniCruce, finCruce;
    int maxIzq = cantDiasMenorPeso(arr,inicio,medio,pesoMenor,iniIzq,finIzq);
    int maxDer = cantDiasMenorPeso(arr,medio+1,fin,pesoMenor,iniDer,finDer);
    int cruce = maxSubArrayCruce(arr,inicio,medio,fin,pesoMenor,iniCruce,finCruce);

    // return max3(maxIzq,maxDer,cruce); retornaba el número de días consecutivos del pesoMenor
    int mejor;
    if (maxIzq>=maxDer && maxIzq>=cruce){
        mejor = maxIzq;
        iniMejor = iniIzq;
        finMejor = finIzq;
    }else if (cruce>=maxDer) {
        mejor = cruce;
        iniMejor = iniCruce;
        finMejor = finCruce;
    }else {
        mejor = maxDer;
        iniMejor = iniDer;
        finMejor = finDer;
    }
    return mejor;
}


int main() {
    ifstream input("datos.txt");
    int dias[N]= {};
    for (int i = 0; i < N; ++i) {
        input>>dias[i];
    }
    int pesoMenor = obtenerMenorNumero(dias,0,N-1);
    int iniMejor,finMejor;
    cout<<"El menor peso fue: "<<pesoMenor<<endl;
    cantDiasMenorPeso(dias,0,N-1,pesoMenor,iniMejor,finMejor);
    cout<<"El rango de días en que lo obtuvo fue del "<<iniMejor+1<<" al "<<finMejor+1<<endl;

    return 0;
}
