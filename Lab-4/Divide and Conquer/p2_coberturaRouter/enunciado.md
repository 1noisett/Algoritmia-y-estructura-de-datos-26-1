# Problema 2 — Mapa de cobertura de un router
**Tema: Picos / look-ahead unimodal (mesetas) + pico 2D.**

Un edificio se modela como una matriz `MAX_FIL × MAX_COL` de **intensidad de señal**.
Cada **fila** es unimodal por columnas: la señal **sube** hasta el pasillo del router y
luego **baja**. La cima (y a veces las laderas) puede tener **valores repetidos
consecutivos**. El router está en la celda de intensidad máxima global.

```cpp
#define MAX_FIL 6
#define MAX_COL 9
int senal[MAX_FIL][MAX_COL] = {
    {10, 20, 20, 35, 50, 48, 30, 15,  5},   // meseta de ladera ancho 2 antes de subir
    {12, 25, 40, 70, 70, 60, 44, 22,  8},
    {15, 33, 55, 80, 95, 95, 60, 30, 10},   // cima ancha
    {20, 40, 66, 66, 90, 99, 70, 40, 18},   // <-- fila del router (99)
    { 8, 16, 30, 52, 74, 60, 40, 20,  6},
    { 5, 14, 28, 44, 44, 38, 30, 18,  9}
};
```

Resuelve, con búsqueda de pico (divide y vencerás), **sin recorrer toda la fila/columna**:

- **(a)** Por cada fila, halla la **columna** de su valor pico y, comparando entre filas,
  reporta la **intensidad máxima global** junto con su **(fila, columna)**.
- **(b)** Sobre la **columna del router** hallada en (a), confirma la **fila** del router
  haciendo búsqueda de pico **por filas** (la columna es unimodal por filas).

> Cuidado: hay mesetas en las laderas. Una comparación `<` / `<=` ingenua puede caer en
> una meseta y devolver una columna equivocada. Mira bien el ancho de los empates en los
> datos y elige el look-ahead correcto. Salida esperada: máximo 99 en (fila 3, columna 5).
