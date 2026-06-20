# Problema 3 — Control de acceso a un data center
**Tema: Paridad / elemento único + mergeSort.**

Cada fila de la matriz son los **registros de huella** (un entero por empleado) de una
sala durante el día. Un empleado genera **dos** registros: uno al **entrar** y otro al
**salir** (mismo código). Al cierre, **a lo más un** empleado se quedó adentro, así que su
código aparece **una sola vez**; el resto aparece en parejas. Los registros llegan
**desordenados**, y algunas posiciones iniciales pueden venir como **ceros de relleno**
(huellas no usadas) que debes ignorar.

```cpp
#define N 8
int registros[N][N] = {
    {0, 0, 5, 5, 9, 2, 2, 9},   // todos en parejas -> nadie quedó adentro
    {0, 7, 3, 7, 4, 3, 4, 1},   // el 1 quedó sin pareja
    {6, 6, 8, 2, 8, 2, 9, 9},   // todos en parejas
    {0, 0, 0, 4, 4, 7, 9, 7},   // el 9 quedó sin pareja
    {3, 1, 3, 1, 5, 8, 8, 5},   // todos en parejas
    {0, 2, 5, 2, 5, 6, 7, 6},   // el 7 quedó sin pareja
    {4, 4, 0, 0, 0, 0, 1, 1},   // todos en parejas
    {0, 0, 9, 3, 9, 3, 6, 6}    // ... resuélvelo tú
};
```

Para **cada fila**, en **O(n log n)** la parte de orden y **O(log n)** la búsqueda:

- **(a)** Ordena la fila con **mergeSort** (impleméntalo, no uses `sort`).
- **(b)** Determina si quedó alguien adentro. Si la cantidad de registros **reales**
  (descartando los ceros de relleno) es **par**, imprime `"Sala despejada"`. Si es
  **impar**, encuentra el **código sin pareja** con búsqueda binaria por **paridad de
  índice**, teniendo en cuenta el **offset** donde terminan los ceros.

> Pista de diseño (no de solución): después de ordenar, los ceros quedan al inicio; el
> primer índice "real" es tu offset, y la paridad se mide **relativa a ese offset**.
