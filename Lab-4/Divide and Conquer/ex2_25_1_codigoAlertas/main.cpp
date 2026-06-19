#include <iostream>
using namespace std;

int encontrarNum(int *arr,int inicio,int fin) {
    if (inicio==fin) return inicio;
    int medio = inicio + (fin-inicio)/2;

    if (arr[medio]<arr[fin]) {
        return encontrarNum(arr,inicio,medio);
    }else {
       return encontrarNum(arr,medio+1,fin);
    }
}

int encontrar(int *arr,int inicio,int fin,int codAlerta) {
    if (inicio==fin) {
        if (arr[inicio]==codAlerta) {
            return inicio;
        }else {
            return -1;
        }
    }
    int medio = inicio + (fin-inicio)/2;

    if (arr[medio]<codAlerta) {
        return encontrar(arr,medio+1,fin,codAlerta);
    }else {
        return encontrar(arr,inicio,medio,codAlerta);
    }
}

int encontrarIndice(int *arr,int codAlerta,int indiceRotado,int inicio,int fin) {
    if (arr[indiceRotado]==codAlerta) {
        return indiceRotado;
    }else if (codAlerta>arr[indiceRotado] && codAlerta<=arr[fin]) {
        return encontrar(arr,indiceRotado,fin,codAlerta);
    }else {
        return encontrar(arr,inicio,indiceRotado-1,codAlerta);
    }
}

int main() {
    int arr[] = {300, 350, 400, 450, 500, 550, 600, 650, 100, 145, 190, 235, 280};
    int n = sizeof(arr)/sizeof(arr[0]);
    int indiceRotado = encontrarNum(arr,0,n-1);
    int codAlerta = 150;
    if (encontrarIndice(arr,codAlerta,indiceRotado,0,n-1)==-1) {
        cout<<"Código "<<codAlerta<<" no se ha encontrado"<<endl;
    }else {
        cout<<encontrarIndice(arr,codAlerta,indiceRotado,0,n-1)+1<<endl;
    }

    return 0;
}
