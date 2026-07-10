# Cola de Prioridad (con lista enlazada) — Apunte para examen

## La idea en una frase

Es una cola normal (`head`, `tail`) a la que se le agrega **un puntero extra**
(`last1`) que apunta al **último elemento de prioridad alta**. Con ese puntero,
encolar y desencolar quedan en **O(1)**.

## Invariante (lo que SIEMPRE debe cumplirse)

La cola se mantiene ordenada por zonas: primero todos los P1, luego todos los P2.
Dentro de cada zona, orden de llegada (FIFO).

```
head → [P1] → [P1] → [P1] → [P2] → [P2] → nullptr
                      ↑                ↑
                    last1            tail
```

`last1` marca la **frontera** entre zonas. Si no hay ningún P1, `last1 == nullptr`.

## El TAD

```cpp
struct Cola {
    NodoCola *head;   // frente (de aquí se atiende)
    NodoCola *tail;   // final absoluto
    NodoCola *last1;  // ⭐ último nodo P1 (nullptr si no hay P1s)
    int longitud;
};
```

## encolar: 4 casos

| Caso | Situación | Qué hacer |
|------|-----------|-----------|
| 1 | Cola vacía | `head = tail = nuevo`; si es P1, también `last1 = nuevo` |
| 2 | Llega P1 y `last1 == nullptr` (solo hay P2) | Insertar al **frente**: `nuevo->sig = head; head = last1 = nuevo` |
| 3 | Llega P1 y ya hay P1s | Insertar **después de `last1`**; si `last1 == tail`, actualizar `tail`; luego `last1 = nuevo` |
| 4 | Llega P2 | Al final normal: `tail->sig = nuevo; tail = nuevo` |

Código del caso 3 (el que más se olvida):

```cpp
nuevo->siguiente = colaTAD.last1->siguiente;
colaTAD.last1->siguiente = nuevo;
if (colaTAD.last1 == colaTAD.tail)   // no había P2s → nuevo fin
    colaTAD.tail = nuevo;
colaTAD.last1 = nuevo;
```

## desencolar: cola normal + UN detalle

Siempre sale el `head` (los P1 ya están adelante, no hay que buscar nada).

```cpp
NodoCola *nodoBorrar = colaTAD.head;
colaTAD.head = nodoBorrar->siguiente;

if (colaTAD.last1 == nodoBorrar)   // ⭐ salió el último P1
    colaTAD.last1 = nullptr;       //    la zona P1 quedó vacía

if (colaTAD.head == nullptr)       // cola quedó vacía
    colaTAD.tail = nullptr;

colaTAD.longitud--;
delete nodoBorrar;
```

## Errores típicos de examen (checklist)

- [ ] Olvidar `last1 = nullptr` al desencolar el último P1 → puntero colgante,
      el siguiente encolar P1 inserta después de un nodo borrado. **El error #1.**
- [ ] En caso 3, olvidar actualizar `tail` cuando `last1 == tail`
      (pasa cuando la cola solo tiene P1s).
- [ ] En caso 2, olvidar poner `last1 = nuevo` (el P1 que entra al frente
      es también el último P1).
- [ ] Olvidar `tail = nullptr` cuando la cola queda vacía.
- [ ] Inicializar `last1` en `construirCola`.

## Generalización (si hay 3+ prioridades)

Misma lógica: un puntero "último de prioridad k" por cada nivel
(`last1`, `last2`, ...). Al encolar prioridad k, se inserta después de
`lastK`; si `lastK == nullptr`, se busca la frontera con el último puntero
no nulo de prioridad más alta (o el `head` si no hay ninguno).

## Complejidad

Todo O(1): encolar, desencolar, esVacia, longitud.
Sin el puntero `last1`, encolar un P1 sería O(n) (recorrer hasta la frontera).

*Basado en `Examen-1/Colas/ex1_25_2` (cola de banco P1/P2).*
