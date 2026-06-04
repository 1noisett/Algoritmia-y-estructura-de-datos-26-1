#include <iostream>
using namespace std;

int encontrarUltimoCero(int *arr,int inicio,int fin) {
    if (inicio==fin) return arr[inicio];

    int medio = inicio + (fin - inicio)/2;

    if (arr[medio] <= 0) {
        return encontrarUltimoCero(arr,medio,fin);
    }else {
        return
    }
}


int main() {
    int arr[] = {-1, 0, -1, 0, 1, 1, 2, 2, 3, 3, 4, 3, 3, 2, 2, 1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int indUltCero = encontrarUltimoCero(arr,0,n-1);
    return 0;
}
