# Examen de práctica final — Divide & Conquer

> 4 problemas combinados, estilo examen real. Uno por tema. **Sin soluciones.**
> Todo en C++, recursivo, respetando la complejidad pedida. Las trampas están en los
> datos: detectarlas (meseta, offset, cruce, rotación) es parte de la nota.
>
> **Regla de oro:** primero identifica *qué predicado parte el rango* (o *cómo se arma el
> cruce*), recién ahí escribe código. Cuando termines los 4, pídeme corregir o ver soluciones.

Tiempo sugerido: **90–110 min** (como un parcial real).

---

## Problema 1 — Monitoreo bancario antifraude
**Tema: Monótonos true/false (decrease & conquer).**

Un banco guarda los montos (en soles) de las transacciones del día en un arreglo
**ordenado ascendentemente**. El sistema antifraude define un umbral `U`: toda
transacción cuyo monto sea **estrictamente mayor** que `U` se marca como *sospechosa*.

```cpp
int montos[] = {12, 30, 45, 45, 80, 110, 150, 150, 220, 300, 480, 900};
// n = 12,  U = 150,  M = 45  (monto a verificar)
```

Resuelve, **todo en O(log n)** (nada de barridos lineales):

- **(a)** Devuelve la **posición de la primera** transacción sospechosa (el primer índice
  cuyo monto es `> U`). Con eso, indica **cuántas** transacciones son sospechosas.
- **(b)** Verifica si existe una transacción de monto **exacto** `M`. Si existe, devuelve
  **cualquier** posición donde aparezca; si no, devuelve `-1` e imprime "no registrada".

> Salida esperada con los datos de arriba:
> primera sospechosa en índice 8 (monto 220) → 4 sospechosas; monto 45 sí registrado.
> Ojo con los empates (montos repetidos): tu predicado debe seguir partiendo bien el rango.

---

## Problema 2 — Mapa de cobertura de un router
**Tema: Picos / look-ahead unimodal (mesetas) + pico 2D.**

Un edificio se modela como una matriz `MAX_FIL × MAX_COL` de **intensidad de señal**.
Cada **fila** es unimodal por columnas: la señal **sube** hasta el pasillo del router y
luego **baja**. La cima (y a veces las laderas) puede tener **valores repetidos
consecutivos**. El router está en la celda de intensidad máxima global.

```cpp
#define MAX_FIL 6
#define MAX_COL 9
int señal[MAX_FIL][MAX_COL] = {
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

---

## Problema 3 — Control de acceso a un data center
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

---

## Problema 4 — Flujo de caja de una startup
**Tema: Divide y vencerás de combinación (ambas mitades + cruce).**

Tienes las **variaciones diarias** del saldo de caja de una startup (positivas = ingreso,
negativas = gasto). Un "tramo" es un subarreglo **contiguo** de días.

```cpp
int flujo[] = {-4, 5, 6, -4, 3, -1, -5, 6, 2, -3};
// n = 10
```

Todo con **divide y vencerás** (recurres por ambas mitades + combinas el caso cruce que
toca el medio). **No** se permite la solución O(n²) de fuerza bruta:

- **(a)** Halla la **mejor racha**: el tramo contiguo de **suma máxima**, y devuelve además
  el **rango de días `[i, j]`** (1-indexado) donde ocurre — usa parámetros por referencia
  para rastrear el rango, no solo el valor.
- **(b)** Halla la **peor racha**: el tramo contiguo de **suma mínima** (la más negativa),
  con su rango. *Es el espejo de (a): cambia los `max` por `min` en los tres frentes
  (izquierda, derecha y cruce).*

> Verifica a mano un caso chico para asegurarte de que el **cruce** arma bien el tramo: el
> bloque que pasa por el medio se extiende desde `medio` hacia ambos lados eligiendo la
> mejor extensión. El rango debe coincidir exactamente con la suma reportada.

---

## Checklist antes de entregarte a ti mismo

- [ ] **P1**: ¿tu predicado `> U` y el binary-search exacto sobreviven a los empates? ¿todo O(log n)?
- [ ] **P2**: ¿elegiste el look-ahead correcto para las mesetas de ladera? ¿2D = pico por fila → pico por columna?
- [ ] **P3**: ¿mergeSort propio? ¿la paridad la mides **relativa al offset** de los ceros?
- [ ] **P4**: ¿el caso cruce arma el rango correcto? ¿(b) es realmente el espejo de (a)?

Cuando termines, dime **"corrige el problema X"** o **"muéstrame la solución del X"**.
