# Divide and Conquer — Roadmap de Active Recall

> Ruta de estudio para repasar toda la carpeta. El orden va de la plantilla base
> a lo compuesto: cada reto se apoya en recordar el anterior.
> **Método:** tapa la función, reprodúcela en papel/editor, y RECIÉN AHÍ compara con el archivo.

---

## Las dos familias (no es una sola)

- **Monótonos (true/false):** bajas por **UNA** mitad según un predicado.
  *Decrease & conquer*, O(log n).
- **Divide y vencerás de combinación:** recurres por **AMBAS** mitades y **combinas**
  (el truco está en el "caso cruce"). O(n log n) / O(n).
- **Picos / look-ahead (unimodal):** familia aparte, ya cubierta
  (ver `clasificacion_picos` más abajo).

---

## Empieza aquí: `teoria/binarySearch`

Núcleo de TODO lo monótono. Si no lo escribes de memoria
(caso base `inicio==fin`, `medio`, descartar media), nada más se sostiene.

---

## Bloque 1 — Monótonos true/false (1 transición)

| # | Ejercicio | Predicado que debes recordar |
|---|-----------|------------------------------|
| 1 | `ejercicios/ContarCeros` (`buscarPrimerCero`) | `111...000` → primera posición con `arr[mid]==0` |
| 2 | `oppenheimer_lab3_24_1/primerPositivo` | primer índice con `arr[mid] > 0` |
| 3 | `ejercicios/encontrarMinimo` | comparar contra el extremo: `arr[medio] > arr[fin]` |
| 4 | `matrizMinerales/contarMinerales` | combina `primerPositivo` + `obtenerPrimerCeroDer` |

**Reto del bloque:** identificar *cuál es el predicado* que parte el rango. Eso es el 90% del problema.

## Bloque 2 — Monótono con paridad (elemento único)

| # | Ejercicio | Qué recordar |
|---|-----------|--------------|
| 5 | `ejercicios/encontrarUnico` | `1,1,2,2,3,...` → la paridad del índice rompe la pareja |
| 6 | `ejercicioAves/encontrarUnicoElemento` | misma idea **con `inicioZona`** (offset) |
| 7 | `bocaditosMatriz` / `inAndOutDataCenter` | aplicar lo anterior, pero **primero ordenar con mergeSort** → puente al Bloque 4 |

## Bloque 3 — Picos / look-ahead (REPASO, ya dominado)

Solo verifica que aún los reproduces:
`ejercicios/encontrarValorMax` → `matrizMinerales` (`+2`) → 2D `matrizBombaTresMesetas` / `bocaditosMatriz` parte (b).
Detalle completo en `clasificacion_picos.md` (si lo generaste).

## Bloque 4 — Divide y vencerás de combinación (ambas mitades + cruce)

| # | Ejercicio | Insight del "cruce" a recordar |
|---|-----------|-------------------------------|
| 8 | `ejercicioAves/mergeSort` + `merge` | la **plantilla** de esta familia |
| 9 | `ejercicios/MaxSubArray` | suma contigua máx = `max(izq, der, cruce)`; el cruce se arma desde el medio hacia ambos lados |
| 10 | `dataLossPrevention` | misma plantilla, **espejo** (mínima suma / más negativa) |
| 11 | `nutricionistaPeso` | racha más larga de un valor **+ rastrear el rango** por referencia (`&`) |
| 12 | `ejercicios/ContarInversiones` | mergeSort **instrumentado** (`inv += medio - i + 1`) |
| 13 | `elegirMejorEmpresa` | max/count por mitades + criterio compuesto |

---

## Cómo verificar que "lo sabes"

No es reconocer la función, es poder escribir desde cero:
1. el **caso base**,
2. **qué predicado/comparación** decide el lado (Bloques 1–3), o **cómo se arma el cruce** (Bloque 4),
3. **qué se combina** al volver.

## Arranque concreto recomendado

`binarySearch` → `ContarCeros` → `encontrarMinimo` → `encontrarUnico`.
Esos cuatro fijan el patrón monótono completo (transición simple + paridad).
Cuando los escribas sin mirar, salta al Bloque 4 con `mergeSort` y `MaxSubArray`,
que son la base de los 4 restantes.
</content>
</invoke>
