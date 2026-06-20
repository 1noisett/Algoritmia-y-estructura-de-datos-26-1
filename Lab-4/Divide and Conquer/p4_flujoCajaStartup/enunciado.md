# Problema 4 — Flujo de caja de una startup
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
