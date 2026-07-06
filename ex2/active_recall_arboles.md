# Árboles (AB / ABB / AVL) — Roadmap de Active Recall

> Complemento del `active_recall_divide_and_conquer.md` (en esta misma carpeta).
> **Método:** tapa la función, escríbela de memoria en el editor, compila, prueba,
> y RECIÉN AHÍ compara con el original. Reconocer no es saber; reproducir sí.

---

## Los tres núcleos (todo lo demás son variantes)

1. **AB — recursión estructural:** casi toda función de árbol es
   `caso base (nodo vacío) → recurro izq → recurro der → combino`.
2. **ABB — el invariante de orden:** `izq < nodo < der` decide por dónde bajar.
   Insertar, buscar y eliminar son la MISMA bajada con distinto final.
3. **AVL — reparar el invariante de altura:** factor de equilibrio + 4 casos de rotación.

---

## Bloque 1 — Núcleo AB (`Lab-4/Trees/FuncionesArboles`)

Escribir de memoria, en este orden (cada una usa la anterior):

| # | Función | Lo que debes recordar sin mirar |
|---|---------|--------------------------------|
| 1 | `recorrerPreOrder/InOrder/PostOrder` | solo cambia DÓNDE va el `imprimir` respecto a las 2 llamadas |
| 2 | `numeroNodos` | `1 + izq + der`; base devuelve 0 |
| 3 | `numeroHojas` | base extra: sin hijos → 1 |
| 4 | `altura` | `1 + max(izq, der)`; convención del vacío (−1 o 0, la del curso) |
| 5 | `esEquilibrado` | `|h(izq) − h(der)| ≤ 1` **y** ambos subárboles equilibrados |
| 6 | `destruirRecursivo` | ¿por qué tiene que ser post-order? |

## Bloque 2 — Construir AB desde un arreglo

| # | Ejercicio | Insight |
|---|-----------|---------|
| 7 | `funcionesAB_PilaYCola/llenarArbol` | mitades tipo búsqueda binaria → árbol balanceado (¡es D&C aplicado!) |
| 8 | `Lab-5/AB/lab4_22_2_cromosomas` | índices estilo heap: hijos en `2*idx+1` y `2*idx+2` |
| 9 | `funcionesAB_PilaYCola` (recorrido con Cola) | por niveles = BFS: encolar raíz, desencolar, encolar hijos |

## Bloque 3 — Núcleo ABB (`Lab-4/Trees/FuncionesABB`)

| # | Función | Lo que debes recordar |
|---|---------|----------------------|
| 10 | `insertarRecursivo` | bajada por comparación; el `*&` (referencia a puntero) es lo que engancha el nodo nuevo |
| 11 | `buscarRecursivo` | misma bajada, devuelve bool; base: vacío → false |
| 12 | `minimoArbol` | bajar siempre a la izquierda |
| 13 | `eliminarRecursivo` | LOS 3 CASOS: hoja / un hijo / dos hijos (sucesor = mínimo del subárbol derecho, copiar y eliminar el sucesor) |

**Test real del Bloque 3:** en `lab4_24_1_paletas`, `lab4_24_2_vinos` y
`lab5_25_2_skynerd` la biblioteca tiene `eliminar` COMENTADO.
Reescríbelo ahí de memoria y compila. Sin mirar FuncionesABB.

## Bloque 4 — ABB aplicados (patrón de examen)

| # | Ejercicio | Qué patrón entrena |
|---|-----------|--------------------|
| 14 | `ex2_25_2_completarFunciones` | insertar/eliminar puros — calentamiento |
| 15 | `lab4_22_1_despachos` | buscar + eliminar según criterio del enunciado |
| 16 | `lab4_22_1_primaryKeys` | rechazar duplicados: verificar ANTES de insertar; devolver nodo, no bool |
| 17 | `lab4_24_2_vinos` | inserción con criterio propio + **búsqueda iterativa** (while, sin recursión) + Pila |
| 18 | `lab4_24_1_paletas` | mergeSort → insertar mitades = ABB balanceado (une D&C + ABB, MUY de examen) |
| 19 | `lab5_25_1_almacenes` / `examen2_24_1_emociones` | recorrido por niveles con Cola + lógica sobre cada nodo |
| 20 | `lab5_25_2_skynerd` | recorrido que DEVUELVE un nodo + destruir un subárbol (y dejar hijos en nullptr) |

## Bloque 5 — AVL (`rotacionesAVL`)

| # | Función | Lo que debes recordar |
|---|---------|----------------------|
| 21 | `rotacionDerecha` / `rotacionIzquierda` | quién es la nueva raíz y qué subárbol se "transplanta" (dibújalo SIEMPRE) |
| 22 | factor de equilibrio | `h(izq) − h(der)`; desbalance si |fe| > 1 |
| 23 | `insertarAVLRecursivo` | los 4 casos: II→rotDer, DD→rotIzq, ID→rotIzq(izq)+rotDer, DI→rotDer(der)+rotIzq |

También en papel: dado un ABB, insertar una secuencia y decir qué rotaciones dispara.

---

## Cómo verificar que "lo sabes"

Para cada función, sin mirar:
1. el **caso base** exacto,
2. si el parámetro es `Nodo*` o `Nodo*&` (¿modifico el enganche o solo leo?),
3. **qué devuelvo/combino** al volver.

Si dudas en 2, no lo sabes todavía: es el error #1 en árboles.

## Orden de arranque recomendado

`altura` → `esEquilibrado` → `insertarRecursivo` → `eliminarRecursivo` (en paletas, que está comentado) → `llenarArbol` → rotaciones AVL.
Esos 6 cubren el 80% de lo que preguntan; el resto son variantes con historia.
