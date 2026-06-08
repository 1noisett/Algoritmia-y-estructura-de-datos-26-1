#include <iostream>
using namespace std;

void merge(int *arr,int inicio,int medio,int fin) {
    int n = fin-inicio+1;
    int temp[n];

    int i = inicio;
    int j = medio+1;
    int k = 0;
    while (i<=medio && j<=fin) {
        if (arr[i]>arr[j]) {
            temp[k] = arr[j];
            j++;
        }else {
            temp[k] = arr[i];
            i++;
        }
        k++;
    }
    while (i<=medio) {
        temp[k] = arr[i]; i++; k++;
    }
    while (j<=fin) {
        temp[k] = arr[j]; j++; k++;
    }
    for (int x = 0; x < k; ++x) {
        arr[inicio+x] = temp[x];
    }
}

void mergeSort(int *arr,int inicio,int fin) {
    if (inicio==fin) return;
    int medio = (inicio+fin)/2;
    mergeSort(arr,inicio,medio);
    mergeSort(arr,medio+1,fin);
    merge(arr,inicio,medio,fin);
}

int encontrarUnicoElemento(int *arr,int inicio,int fin) {
    if (inicio==fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;

    if (medio%2==0) {
        if (arr[medio] == arr[medio+1]) {
            return encontrarUnicoElemento(arr,medio+2,fin);
        }else {
            return encontrarUnicoElemento(arr,inicio,medio);
        }
    }else {
        if (arr[medio] == arr[medio-1]) {
            return encontrarUnicoElemento(arr,medio+1,fin);
        }else {
            return encontrarUnicoElemento(arr,inicio,medio);
        }
    }
}

int main() {
    int arr[] = {1, 6, 3, 4, 5, 6, 3, 7, 5, 4, 3, 1, 7};
    int n = sizeof(arr)/sizeof(arr[0]);
    mergeSort(arr,0,n-1);

    for (int i = 0; i < n; ++i) {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    cout<<encontrarUnicoElemento(arr,0,n-1)<<endl;
    return 0;
}
