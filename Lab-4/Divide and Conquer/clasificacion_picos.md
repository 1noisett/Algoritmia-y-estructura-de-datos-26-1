# Búsqueda de pico en arreglos unimodales — clasificación

> Buscar el máximo en un arreglo que "crece y decrece". Toda la dificultad se
> reduce a una pregunta: ¿qué pasa cuando `arr[medio] == arr[medio+1]`? (una **meseta**).

## Principio maestro

Una ventana que mira hasta `medio+k` resuelve **mesetas de LADERA** de ancho ≤ k:

| Look-ahead | Mesetas de ladera que tolera | Costo |
|---|---|---|
| `+1` (`<` o `<=` puro) | ancho ≤ 1 (laderas estrictas) | O(log n) |
| `+2` (`matrizMinerales`) | ancho ≤ 2 | O(log n) |
| `+k` / `while` | ancho ≤ k (k constante) | O(log n) |
| sin cota | ancho arbitrario | O(n) |

**La CIMA puede tener cualquier ancho** sin problema; la restricción de ancho aplica
**solo a las laderas**. (En la cima, "ir a la izquierda" siempre es seguro: converges
al borde izquierdo de la meseta-cima, que también es un máximo.)

---

## Tabla de casos

| # | Caso | Estructura | Algoritmo correcto | Costo |
|---|------|-----------|-------------------|-------|
| A | Pico estricto | sube/baja estricto, sin repetidos | `<` o `<=` puro | O(log n) |
| B | Meseta solo en la cima | laderas **estrictas** + meseta arriba (cualquier ancho) | `<` o `<=` puro | O(log n) |
| C | Simétrico + pico único | espejo izq/der, pico ancho 1 (longitud impar) | `<=` puro — **garantizado** | O(log n) |
| D | Mesetas ancho ≤2 en laderas | empates ancho ≤2, cualquier lado, sin simetría | `+2` (look-ahead) | O(log n) |
| E | Mesetas ancho ≤k en laderas | empates de ancho acotado por constante k | `+k` / `while` | O(log n) |
| F | Mesetas de ancho arbitrario | empates sin cota | barrido lineal | O(n) |
| G | Pico en 2D (matriz) | filas unimodales + columna unimodal | pico por fila → pico por columna | O(filas·log col + log fil) |

---

## A — Pico estricto

```cpp
int buscarMax(int *arr, int inicio, int fin) {
    if (inicio == fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;
    if (arr[medio] < arr[medio+1]) return buscarMax(arr, medio+1, fin); // subida -> der
    else                           return buscarMax(arr, inicio, medio); // bajada -> izq
}
```
Sin empates, `<` y `<=` son idénticos. Caso por defecto.

## B — Meseta solo en la cima (laderas estrictas)

Funciona el d&c puro. Borde según la comparación:
- `<`  → en empate va a la **izquierda** → devuelve el **borde izquierdo** de la cima.
- `<=` → en empate va a la **derecha**   → devuelve el **borde derecho**.

Ej: `{1,5,5,5,5,5,1}` con `<` puro devuelve 5. ⚠️ Solo vale si las laderas son ESTRICTAS.

## C — Simétrico + pico único (caso oppenheimer)

`{1,1,2,2,3,2,2,1,1}` — espejo + pico único (ancho 1) ⇒ longitud impar.

```cpp
int buscarMax(int *arr, int inicio, int fin) {   // +1 con <=
    if (inicio == fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;
    if (arr[medio] <= arr[medio+1]) return buscarMax(arr, medio+1, fin);
    else                            return buscarMax(arr, inicio, medio);
}
```

**Por qué está garantizado (no es suerte):** simétrico + pico único ⇒ el pico está
en el centro ⇒ el primer `medio` cae EXACTO en el pico ⇒ descarta toda la bajada de
un golpe ⇒ queda solo la subida (no-decreciente), donde `<=` siempre acierta.

⚠️ Si rompes la simetría, el pico es ancho ≥2, o la longitud es par → el `+1` puede
caer en una meseta de la bajada y FALLA. Ahí usas D.

## D — Mesetas ancho ≤2 en laderas, sin simetría (`+2`)

`matrizMinerales`. Maneja ancho ≤2 en izq, der o ambos. **No** necesita simetría
ni pico centrado. También maneja cima de cualquier ancho.

```cpp
int buscarMax(int *arr, int inicio, int fin) {
    if (inicio == fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;

    if (arr[medio] == arr[medio+1]) {            // meseta: me asomo a medio+2
        if (medio+2 <= fin && arr[medio+1] < arr[medio+2])
            return buscarMax(arr, medio+1, fin); // tras la meseta SIGUE subiendo -> der
        else
            return buscarMax(arr, inicio, medio); // no sube -> izq
    }
    if (arr[medio] < arr[medio+1]) return buscarMax(arr, medio+1, fin);
    else                           return buscarMax(arr, inicio, medio);
}
```
Con ancho 3 en ladera **NO es confiable** (falla si el `medio` cae al inicio de la meseta).

> Nota: en el caso normal puedes usar `<` en vez de `>` sin problema — son equivalentes
> porque el `==` ya se peló arriba, así que en el caso normal `arr[medio] != arr[medio+1]`.

## E — Versión general mecanizable (cualquier ancho acotado)

En vez de desenrollar `+3`, `+4`… a mano, **salta la meseta hasta el primer valor distinto**:

```cpp
int buscarMax(int *arr, int inicio, int fin) {
    if (inicio == fin) return arr[inicio];
    int medio = inicio + (fin-inicio)/2;

    if (arr[medio] == arr[medio+1]) {            // saltar la meseta hacia adelante
        int j = medio + 1;
        while (j < fin && arr[j] == arr[medio]) j++;
        if (arr[medio] < arr[j]) return buscarMax(arr, j, fin);        // sube tras meseta -> der
        else                     return buscarMax(arr, inicio, medio);  // no sube -> izq
    }
    if (arr[medio] < arr[medio+1]) return buscarMax(arr, medio+1, fin);
    else                           return buscarMax(arr, inicio, medio);
}
```
Ancho acotado por constante → O(log n). Ancho arbitrario → O(n) (caso F).

## G — Pico en 2D (matrizBombaTresMesetas)

1. Por cada fila, hallar la columna del máximo (caso A–E que aplique) → quedarte con el global.
2. Sobre esa columna fija, búsqueda de pico por filas.

---

## Árbol de decisión

```
¿Valores repetidos consecutivos?
├─ NO ............................. A: <  o <=
└─ SÍ
   ├─ ¿Mesetas SOLO en la cima y laderas estrictas? ....... B: puro
   ├─ ¿Simétrico con pico único (impar)? ................. C: <= (garantizado)
   ├─ ¿Mesetas de ladera ancho ≤2, cualquier lado? ....... D: +2
   ├─ ¿Mesetas de ancho acotado por constante k? ......... E: +k / while
   └─ ¿Mesetas de ancho arbitrario? ...................... F: lineal O(n)

¿Matriz 2D unimodal? ............... G: pico por fila -> pico por columna
```

## Contraejemplos clave (para probar los límites)

- `{1,5,5,9,4,2,1}` → el `<` puro FALLA (devuelve 5); el `+2` da 9. (meseta ladera ancho 2)
- `{1,2,9,5,5,3,1}` → el `<=` puro FALLA en la bajada; el `+2` da 9.
- `{1,1,2,2,5,5,2,2,1,1}` → simétrico pero pico ancho 2: el `<=` (+1) FALLA (devuelve 2); el `+2` da 5.
- `{1,2,3,3,3,9}` → el `+2` FALLA (meseta de ladera ancho 3, devuelve 3).
- `{1,5,5,5,5,5,1}` → cima ancha + laderas estrictas: el puro funciona (caso B).
- `{1,5,5,9,9,9,2}` → cima ancha + meseta de ladera: el puro FALLA, el `+2` da 9.
</content>
