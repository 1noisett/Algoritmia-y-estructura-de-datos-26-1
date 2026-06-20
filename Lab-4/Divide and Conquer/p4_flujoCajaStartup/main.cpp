#include <iostream>
using namespace std;

// ===================== (a) MEJOR RACHA: suma máxima + rango =====================

// Cruce: el mejor tramo que TOCA el medio. Extiende hacia ambos lados desde el
// centro y guarda el índice donde se alcanza la mejor suma de cada lado.
int mejorRachaCruce(int *arr, int inicio, int medio, int fin, int &ini, int &fin_) {
    int mejorIzq = arr[medio];
    int suma = 0;
    int idxIzq = medio;                       // el bloque izq SIEMPRE incluye al medio
    for (int i = medio; i >= inicio; --i) {
        suma += arr[i];
        if (suma > mejorIzq) { mejorIzq = suma; idxIzq = i; }
    }

    int mejorDer = arr[medio + 1];
    suma = 0;
    int idxDer = medio + 1;                    // el bloque der SIEMPRE incluye a medio+1
    for (int j = medio + 1; j <= fin; ++j) {
        suma += arr[j];
        if (suma > mejorDer) { mejorDer = suma; idxDer = j; }
    }

    ini  = idxIzq;
    fin_ = idxDer;
    return mejorIzq + mejorDer;
}

int mejorRacha(int *arr, int inicio, int fin, int &ini, int &fin_) {
    if (inicio == fin) { ini = inicio; fin_ = inicio; return arr[inicio]; }
    int medio = inicio + (fin - inicio) / 2;

    int iniIzq, finIzq, iniDer, finDer, iniCruce, finCruce;
    int maxIzq   = mejorRacha(arr, inicio, medio, iniIzq, finIzq);
    int maxDer   = mejorRacha(arr, medio + 1, fin, iniDer, finDer);
    int maxCruce = mejorRachaCruce(arr, inicio, medio, fin, iniCruce, finCruce);

    if (maxIzq >= maxDer && maxIzq >= maxCruce) { ini = iniIzq;   fin_ = finIzq;   return maxIzq; }
    if (maxDer >= maxCruce)                      { ini = iniDer;   fin_ = finDer;   return maxDer; }
    /* gana el cruce */                            ini = iniCruce; fin_ = finCruce; return maxCruce;
}

// ===================== (b) PEOR RACHA: suma mínima + rango (espejo) =====================

int peorRachaCruce(int *arr, int inicio, int medio, int fin, int &ini, int &fin_) {
    int peorIzq = arr[medio];
    int suma = 0;
    int idxIzq = medio;
    for (int i = medio; i >= inicio; --i) {
        suma += arr[i];
        if (suma < peorIzq) { peorIzq = suma; idxIzq = i; }
    }

    int peorDer = arr[medio + 1];
    suma = 0;
    int idxDer = medio + 1;
    for (int j = medio + 1; j <= fin; ++j) {
        suma += arr[j];
        if (suma < peorDer) { peorDer = suma; idxDer = j; }
    }

    ini  = idxIzq;
    fin_ = idxDer;
    return peorIzq + peorDer;
}

int peorRacha(int *arr, int inicio, int fin, int &ini, int &fin_) {
    if (inicio == fin) { ini = inicio; fin_ = inicio; return arr[inicio]; }
    int medio = inicio + (fin - inicio) / 2;

    int iniIzq, finIzq, iniDer, finDer, iniCruce, finCruce;
    int minIzq   = peorRacha(arr, inicio, medio, iniIzq, finIzq);
    int minDer   = peorRacha(arr, medio + 1, fin, iniDer, finDer);
    int minCruce = peorRachaCruce(arr, inicio, medio, fin, iniCruce, finCruce);

    if (minIzq <= minDer && minIzq <= minCruce) { ini = iniIzq;   fin_ = finIzq;   return minIzq; }
    if (minDer <= minCruce)                      { ini = iniDer;   fin_ = finDer;   return minDer; }
    /* gana el cruce */                            ini = iniCruce; fin_ = finCruce; return minCruce;
}

int main() {
    int flujo[] = {-4, 5, 6, -4, 3, -1, -5, 6, 2, -3};
    int n = sizeof(flujo) / sizeof(flujo[0]);

    int iniA, finA;
    int sumaMax = mejorRacha(flujo, 0, n - 1, iniA, finA);
    cout << "Mejor racha: suma " << sumaMax
         << " (dias " << iniA + 1 << " al " << finA + 1 << ")" << endl;

    int iniB, finB;
    int sumaMin = peorRacha(flujo, 0, n - 1, iniB, finB);
    cout << "Peor racha: suma " << sumaMin
         << " (dias " << iniB + 1 << " al " << finB + 1 << ")" << endl;

    return 0;
}
