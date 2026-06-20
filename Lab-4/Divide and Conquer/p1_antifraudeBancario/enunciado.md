# Problema 1 — Monitoreo bancario antifraude
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
