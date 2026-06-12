import React, { useState, useEffect, useMemo, useRef } from "react";
import {
  Play,
  Pause,
  RotateCcw,
  ChevronLeft,
  ChevronRight,
  TreePine,
  Code2,
  Layers,
  Terminal,
  Gauge,
} from "lucide-react";

/* ================================================================
   ÁRBOL DE EJEMPLO — exactamente el de main.cpp
            100              Nivel 0
          /     \
        50      150          Nivel 1
      /   \    /   \
    25    80  120   200      Nivel 2
================================================================ */

const TREE = {
  id: "n100",
  val: 100,
  izq: {
    id: "n50",
    val: 50,
    izq: { id: "n25", val: 25, izq: null, der: null },
    der: { id: "n80", val: 80, izq: null, der: null },
  },
  der: {
    id: "n150",
    val: 150,
    izq: { id: "n120", val: 120, izq: null, der: null },
    der: { id: "n200", val: 200, izq: null, der: null },
  },
};

// posición [columna in-order, profundidad] de cada nodo
const POS = {
  n25: [0, 2],
  n50: [1, 1],
  n80: [2, 2],
  n100: [3, 0],
  n120: [4, 2],
  n150: [5, 1],
  n200: [6, 2],
};
const ALL_IDS = Object.keys(POS);
const EDGES = [
  ["n100", "n50"],
  ["n100", "n150"],
  ["n50", "n25"],
  ["n50", "n80"],
  ["n150", "n120"],
  ["n150", "n200"],
];
const xy = (id) => {
  const [slot, depth] = POS[id];
  return { x: 60 + slot * 100, y: 64 + depth * 118 };
};
const valOf = (id) => +id.slice(1);

const NOMBRE_ARBOL = {
  n25: "subarbol25",
  n80: "subarbol80",
  n120: "subarbol120",
  n200: "subarbol200",
  n50: "hijoIzq",
  n150: "hijoDer",
  n100: "arbol",
};

function subtreeIds(node) {
  if (!node) return [];
  return [node.id, ...subtreeIds(node.izq), ...subtreeIds(node.der)];
}

// réplica exacta de alturaRecursivo de FuncionesArbolBinario.cpp
function alturaDe(node) {
  if (!node) return 0;
  if (!node.izq && !node.der) return 0;
  return 1 + Math.max(alturaDe(node.izq), alturaDe(node.der));
}

/* ================================================================
   BLOQUES DE CÓDIGO C++ (de FuncionesArbolBinario.cpp / main.cpp)
================================================================ */

const CODE_PLANTAR = [
  "// ---- main.cpp ----",
  "construir(arbol);  construir(arbolVacio);",
  "plantarArbolBinario(subarbol25, arbolVacio, {25}, arbolVacio);",
  "plantarArbolBinario(subarbol80, arbolVacio, {80}, arbolVacio);",
  "plantarArbolBinario(subarbol120, arbolVacio, {120}, arbolVacio);",
  "plantarArbolBinario(subarbol200, arbolVacio, {200}, arbolVacio);",
  "plantarArbolBinario(hijoIzq, subarbol25, {50}, subarbol80);",
  "plantarArbolBinario(hijoDer, subarbol120, {150}, subarbol200);",
  "plantarArbolBinario(arbol, hijoIzq, {100}, hijoDer);",
  "",
  "// ---- FuncionesArbolBinario.cpp ----",
  "void construir(ArbolBinario &arbol) {",
  "    arbol.raiz = nullptr;",
  "}",
  "",
  "void plantarArbolBinario(ArbolBinario &arbol, const ArbolBinario &izq,",
  "        const ElementoArbolBinario &elemento, const ArbolBinario &der) {",
  "    plantarNodoArbolBinario(arbol.raiz, izq.raiz, elemento, der.raiz);",
  "}",
  "",
  "void plantarNodoArbolBinario(NodoArbolBinario *&nodo, NodoArbolBinario *izq,",
  "        const ElementoArbolBinario &elemento, NodoArbolBinario *der) {",
  "    NodoArbolBinario *nuevo = new NodoArbolBinario;",
  "    nuevo->der = der;",
  "    nuevo->izq = izq;",
  "    nuevo->elemento = elemento;",
  "    nodo = nuevo;",
  "}",
];

const codeTraversal = (Name) => [
  `void recorrer${Name}(const ArbolBinario &arbol) {`,
  `    recorrer${Name}Recursivo(arbol.raiz);`,
  "}",
  "",
  `void recorrer${Name}Recursivo(NodoArbolBinario *nodo) {`,
  "    if (!esNodoVacio(nodo)) {",
  ...{
    PreOrder: [
      "        imprimirNodo(nodo);",
      `        recorrerPreOrderRecursivo(nodo->izq);`,
      `        recorrerPreOrderRecursivo(nodo->der);`,
    ],
    InOrder: [
      `        recorrerInOrderRecursivo(nodo->izq);`,
      "        imprimirNodo(nodo);",
      `        recorrerInOrderRecursivo(nodo->der);`,
    ],
    PostOrder: [
      `        recorrerPostOrderRecursivo(nodo->izq);`,
      `        recorrerPostOrderRecursivo(nodo->der);`,
      "        imprimirNodo(nodo);",
    ],
  }[Name],
  "    }",
  "}",
];

const CODE_NODOS = [
  "int numeroNodos(const ArbolBinario &arbol) {",
  "    return numeroNodosRecursivo(arbol.raiz);",
  "}",
  "",
  "int numeroNodosRecursivo(NodoArbolBinario *nodo) {",
  "    if (esNodoVacio(nodo)) {",
  "        return 0;",
  "    } else {",
  "        return 1 + numeroNodosRecursivo(nodo->izq)",
  "                 + numeroNodosRecursivo(nodo->der);",
  "    }",
  "}",
];

const CODE_HOJAS = [
  "int numeroHojas(const ArbolBinario &arbol) {",
  "    return numeroHojasRecursivo(arbol.raiz);",
  "}",
  "",
  "int numeroHojasRecursivo(NodoArbolBinario *nodo) {",
  "    if (esNodoVacio(nodo)) {",
  "        return 0;",
  "    } else if (nodo->izq == nullptr && nodo->der == nullptr) {",
  "        return 1;",
  "    } else {",
  "        return numeroHojasRecursivo(nodo->izq)",
  "             + numeroHojasRecursivo(nodo->der);",
  "    }",
  "}",
];

const CODE_ALTURA = [
  "int maximo(int num1, int num2) {",
  "    return (num1 >= num2) ? num1 : num2;",
  "}",
  "",
  "int altura(const ArbolBinario &arbol) {",
  "    return alturaRecursivo(arbol.raiz);",
  "}",
  "",
  "int alturaRecursivo(NodoArbolBinario *nodo) {",
  "    if (esNodoVacio(nodo)) {",
  "        return 0;",
  "    } else if (nodo->izq == nullptr && nodo->der == nullptr) {",
  "        return 0;",
  "    } else {",
  "        return 1 + maximo(alturaRecursivo(nodo->izq),",
  "                          alturaRecursivo(nodo->der));",
  "    }",
  "}",
];

const CODE_EQ = [
  "bool esEquilibrado(const ArbolBinario &arbol) {",
  "    return esEquilibradoRecursivo(arbol.raiz);",
  "}",
  "",
  "bool esEquilibradoRecursivo(NodoArbolBinario *nodo) {",
  "    if (esNodoVacio(nodo)) {",
  "        return true;",
  "    } else {",
  "        int alturaIzq = alturaRecursivo(nodo->izq);",
  "        int alturaDer = alturaRecursivo(nodo->der);",
  "        int diferencia = abs(alturaIzq - alturaDer);",
  "        return diferencia <= 1",
  "            && esEquilibradoRecursivo(nodo->izq)",
  "            && esEquilibradoRecursivo(nodo->der);",
  "    }",
  "}",
];

/* ================================================================
   STEP GENERATOR
   Cada generador re-ejecuta la recursión del C++ en JS y emite
   "frames" inmutables: { line, desc, states, labels, stack,
   output, ghost, flash, visible, edges, noNum }.
   Avanzar/retroceder = mover un índice sobre el array de frames.
================================================================ */

function builder(opts = {}) {
  const frames = [];
  const st = {
    states: Object.fromEntries(ALL_IDS.map((id) => [id, "idle"])),
    labels: {},
    stack: [],
    output: [],
    visible: opts.progressive ? new Set() : null,
    edges: opts.progressive ? new Set() : null,
    noNum: opts.progressive ? new Set() : null,
  };
  const emit = (line, desc, extra = {}) =>
    frames.push({
      line,
      desc,
      states: { ...st.states },
      labels: { ...st.labels },
      stack: [...st.stack],
      output: [...st.output],
      ghost: extra.ghost || null,
      flash: extra.flash || [],
      visible: st.visible && new Set(st.visible),
      edges: st.edges && new Set(st.edges),
      noNum: st.noNum && new Set(st.noNum),
    });
  return { frames, st, emit };
}

/* ---------- construir / plantar ---------- */

function genPlantar() {
  const { frames, st, emit } = builder({ progressive: true });
  emit(
    1,
    "construir(arbol) y construir(arbolVacio): ambos árboles quedan con raiz = nullptr. El lienzo está vacío."
  );
  emit(
    12,
    "arbol.raiz = nullptr → un árbol recién construido no tiene ningún nodo. arbolVacio servirá para plantar hojas (hijos vacíos)."
  );
  const plants = [
    { id: "n25", main: 2, izq: null, der: null },
    { id: "n80", main: 3, izq: null, der: null },
    { id: "n120", main: 4, izq: null, der: null },
    { id: "n200", main: 5, izq: null, der: null },
    { id: "n50", main: 6, izq: "n25", der: "n80" },
    { id: "n150", main: 7, izq: "n120", der: "n200" },
    { id: "n100", main: 8, izq: "n50", der: "n150" },
  ];
  for (const p of plants) {
    const val = valOf(p.id);
    const nombre = NOMBRE_ARBOL[p.id];
    emit(
      p.main,
      `main: se planta ${nombre} con elemento {${val}}` +
        (p.izq
          ? `, hijo izquierdo = ${NOMBRE_ARBOL[p.izq]} y hijo derecho = ${NOMBRE_ARBOL[p.der]}.`
          : " y ambos hijos vacíos (arbolVacio).")
    );
    emit(
      17,
      "plantarArbolBinario delega en plantarNodoArbolBinario: pasa arbol.raiz por referencia (para poder modificarla) y las raíces de los subárboles izq y der."
    );
    st.visible.add(p.id);
    st.noNum.add(p.id);
    st.states[p.id] = "active";
    emit(
      22,
      "new NodoArbolBinario reserva memoria en el heap: el nodo ya existe, pero sus campos todavía no tienen valores asignados."
    );
    if (p.der) st.edges.add(`${p.id}-${p.der}`);
    emit(
      23,
      p.der
        ? `nuevo->der apunta a la raíz de ${NOMBRE_ARBOL[p.der]} (nodo ${valOf(p.der)}). Se conecta la rama derecha.`
        : "nuevo->der = nullptr (der.raiz venía de arbolVacio): este nodo no tendrá hijo derecho."
    );
    if (p.izq) st.edges.add(`${p.id}-${p.izq}`);
    emit(
      24,
      p.izq
        ? `nuevo->izq apunta a la raíz de ${NOMBRE_ARBOL[p.izq]} (nodo ${valOf(p.izq)}). Se conecta la rama izquierda.`
        : "nuevo->izq = nullptr: este nodo no tendrá hijo izquierdo."
    );
    st.noNum.delete(p.id);
    emit(25, `nuevo->elemento = {${val}}: se copia el ElementoArbolBinario dentro del nodo.`);
    st.states[p.id] = "done";
    emit(
      26,
      `nodo = nuevo: como 'nodo' es una referencia a ${nombre}.raiz, el árbol ${nombre} ahora apunta a este nodo. ¡Plantado!`
    );
  }
  emit(
    null,
    "Árbol completo: 7 nodos en 3 niveles, construido de abajo hacia arriba (primero las hojas, al final la raíz)."
  );
  return frames;
}

/* ---------- recorridos pre / in / post ---------- */

function genTraversal(order) {
  const { frames, st, emit } = builder();
  const Name = { pre: "PreOrder", ino: "InOrder", post: "PostOrder" }[order];
  const fname = `recorrer${Name}Recursivo`;
  const ops = {
    pre: ["print", "izq", "der"],
    ino: ["izq", "print", "der"],
    post: ["izq", "der", "print"],
  }[order];
  const lineOf = {
    pre: { print: 6, izq: 7, der: 8 },
    ino: { izq: 6, print: 7, der: 8 },
    post: { izq: 6, der: 7, print: 8 },
  }[order];

  emit(1, `recorrer${Name} llama a ${fname} pasándole la raíz del árbol (nodo 100).`);

  function rec(node, parent, side) {
    if (!node) {
      st.stack.push(`${fname}(nullptr)`);
      emit(
        5,
        `El hijo ${side === "izq" ? "izquierdo" : "derecho"} de ${parent.val} es nullptr → esNodoVacio devuelve true → !true es false. No se entra al if: caso base, la llamada retorna de inmediato.`,
        { ghost: { parentId: parent.id, side } }
      );
      st.stack.pop();
      return;
    }
    st.stack.push(`${fname}(nodo ${node.val})`);
    st.states[node.id] = "active";
    emit(5, `nodo apunta al ${node.val} → esNodoVacio es false → se entra al if.`);
    for (const op of ops) {
      if (op === "print") {
        st.output.push(node.val);
        st.states[node.id] = "printed";
        emit(
          lineOf.print,
          `imprimirNodo(nodo): cout imprime ${node.val} (posición ${st.output.length} de la salida).`
        );
      } else {
        if (st.states[node.id] === "active") st.states[node.id] = "stack";
        emit(
          lineOf[op],
          `Llamada recursiva con el hijo ${op === "izq" ? "izquierdo" : "derecho"} del nodo ${node.val}. La llamada actual queda esperando en la pila.`
        );
        rec(node[op], node, op);
        if (st.states[node.id] === "stack") st.states[node.id] = "active";
      }
    }
    emit(
      10,
      `Fin de ${fname}(${node.val}): la llamada se desapila y el control vuelve ${parent ? `al nodo ${parent.val}` : `a recorrer${Name}`}.`
    );
    st.stack.pop();
  }

  rec(TREE, null, "");
  emit(2, `Recorrido ${Name} terminado. Salida: ${st.output.join("   ")}`);
  return frames;
}

/* ---------- numeroNodos ---------- */

function genNodos() {
  const { frames, st, emit } = builder();
  emit(1, "numeroNodos llama a numeroNodosRecursivo con la raíz (nodo 100).");

  function rec(node, parent, side) {
    if (!node) {
      st.stack.push("numeroNodosRecursivo(nullptr)");
      const g = { ghost: { parentId: parent.id, side } };
      emit(5, `El hijo ${side === "izq" ? "izquierdo" : "derecho"} de ${parent.val} es nullptr → esNodoVacio devuelve true.`, g);
      emit(6, "Caso base: un subárbol vacío aporta 0 nodos → return 0.", g);
      st.stack.pop();
      return 0;
    }
    st.stack.push(`numeroNodosRecursivo(${node.val})`);
    st.states[node.id] = "active";
    emit(5, `esNodoVacio(${node.val}) es false → se va a la rama else.`);
    st.states[node.id] = "stack";
    emit(
      8,
      `Cuenta = 1 (el propio ${node.val}) + nodos de la izquierda + nodos de la derecha. Primero se resuelve la llamada izquierda.`
    );
    const L = rec(node.izq, node, "izq");
    st.labels[node.id] = `izq=${L}`;
    emit(9, `La llamada izquierda de ${node.val} devolvió ${L}. Ahora la llamada derecha.`);
    const R = rec(node.der, node, "der");
    const total = 1 + L + R;
    st.labels[node.id] = `1+${L}+${R}=${total}`;
    st.states[node.id] = "done";
    emit(8, `return 1 + ${L} + ${R} = ${total}: el subárbol con raíz ${node.val} tiene ${total} nodos.`);
    st.stack.pop();
    return total;
  }

  const t = rec(TREE, null, "");
  emit(2, `numeroNodos devuelve ${t}. El árbol tiene ${t} nodos en total.`);
  return frames;
}

/* ---------- numeroHojas ---------- */

function genHojas() {
  const { frames, st, emit } = builder();
  emit(1, "numeroHojas llama a numeroHojasRecursivo con la raíz (nodo 100).");

  function rec(node, parent, side) {
    if (!node) {
      st.stack.push("numeroHojasRecursivo(nullptr)");
      const g = { ghost: { parentId: parent.id, side } };
      emit(5, "nodo es nullptr → esNodoVacio devuelve true.", g);
      emit(6, "Un subárbol vacío no tiene hojas → return 0.", g);
      st.stack.pop();
      return 0;
    }
    st.stack.push(`numeroHojasRecursivo(${node.val})`);
    st.states[node.id] = "active";
    emit(5, `esNodoVacio(${node.val}) es false → se evalúa la siguiente condición.`);
    if (!node.izq && !node.der) {
      emit(7, `nodo->izq y nodo->der del ${node.val} son nullptr → ¡el ${node.val} es una hoja! (Nota: aquí NO hay llamadas recursivas).`);
      st.labels[node.id] = "hoja → 1";
      st.states[node.id] = "done";
      emit(8, `return 1: el nodo ${node.val} cuenta como una hoja.`);
      st.stack.pop();
      return 1;
    }
    emit(7, `El nodo ${node.val} tiene al menos un hijo → no es hoja → rama else.`);
    st.states[node.id] = "stack";
    emit(10, `Se suman las hojas del subárbol izquierdo de ${node.val}…`);
    const L = rec(node.izq, node, "izq");
    st.labels[node.id] = `izq=${L}`;
    emit(11, `La izquierda devolvió ${L} hoja(s). Ahora el subárbol derecho…`);
    const R = rec(node.der, node, "der");
    st.labels[node.id] = `${L}+${R}=${L + R}`;
    st.states[node.id] = "done";
    emit(10, `return ${L} + ${R} = ${L + R}: hojas debajo del nodo ${node.val}.`);
    st.stack.pop();
    return L + R;
  }

  const t = rec(TREE, null, "");
  emit(2, `numeroHojas devuelve ${t}. El árbol tiene ${t} hojas (25, 80, 120 y 200).`);
  return frames;
}

/* ---------- altura ---------- */

function genAltura() {
  const { frames, st, emit } = builder();
  emit(5, "altura llama a alturaRecursivo con la raíz (nodo 100).");

  function rec(node, parent, side) {
    if (!node) {
      st.stack.push("alturaRecursivo(nullptr)");
      const g = { ghost: { parentId: parent.id, side } };
      emit(9, "nodo es nullptr → esNodoVacio devuelve true.", g);
      emit(10, "return 0: un subárbol vacío tiene altura 0.", g);
      st.stack.pop();
      return 0;
    }
    st.stack.push(`alturaRecursivo(${node.val})`);
    st.states[node.id] = "active";
    emit(9, `esNodoVacio(${node.val}) es false → siguiente condición.`);
    if (!node.izq && !node.der) {
      emit(11, `El ${node.val} no tiene hijos → es una hoja.`);
      st.labels[node.id] = "h=0";
      st.states[node.id] = "done";
      emit(12, `return 0: en esta definición, una hoja tiene altura 0 (se cuentan aristas, no nodos).`);
      st.stack.pop();
      return 0;
    }
    emit(11, `El ${node.val} tiene hijos → rama else.`);
    st.states[node.id] = "stack";
    emit(14, `Se necesita la altura del subárbol izquierdo de ${node.val}…`);
    const a = rec(node.izq, node, "izq");
    st.labels[node.id] = `hIzq=${a}`;
    emit(15, `alturaRecursivo(izq) devolvió ${a}. Ahora la altura del subárbol derecho…`);
    const b = rec(node.der, node, "der");
    st.labels[node.id] = `hIzq=${a}  hDer=${b}`;
    const m = Math.max(a, b);
    emit(1, `maximo(${a}, ${b}): como ${a >= b ? `${a} >= ${b}` : `${a} < ${b}`}, devuelve ${m}.`);
    const h = 1 + m;
    st.labels[node.id] = `h=1+${m}=${h}`;
    st.states[node.id] = "done";
    emit(14, `return 1 + ${m} = ${h}: la altura del nodo ${node.val} es ${h} (1 arista hasta el hijo más alto).`);
    st.stack.pop();
    return h;
  }

  const h = rec(TREE, null, "");
  emit(6, `altura devuelve ${h}: hay ${h} niveles de aristas desde la raíz hasta las hojas.`);
  return frames;
}

/* ---------- esEquilibrado ---------- */

function genEquilibrado() {
  const { frames, st, emit } = builder();
  emit(1, "esEquilibrado llama a esEquilibradoRecursivo con la raíz (nodo 100).");

  function rec(node, parent, side) {
    if (!node) {
      st.stack.push("esEquilibradoRecursivo(nullptr)");
      const g = { ghost: { parentId: parent.id, side } };
      emit(5, "nodo es nullptr → esNodoVacio devuelve true.", g);
      emit(6, "Un árbol vacío siempre está equilibrado → return true.", g);
      st.stack.pop();
      return true;
    }
    st.stack.push(`esEquilibradoRecursivo(${node.val})`);
    st.states[node.id] = "active";
    emit(5, `esNodoVacio(${node.val}) es false → rama else.`);
    const a = alturaDe(node.izq);
    const b = alturaDe(node.der);
    st.labels[node.id] = `hIzq=${a}`;
    emit(
      8,
      `alturaRecursivo recorre TODO el subárbol izquierdo de ${node.val} (zona morada) y devuelve alturaIzq = ${a}.`,
      { flash: subtreeIds(node.izq) }
    );
    st.labels[node.id] = `hIzq=${a}  hDer=${b}`;
    emit(
      9,
      `alturaRecursivo recorre el subárbol derecho de ${node.val} y devuelve alturaDer = ${b}.`,
      { flash: subtreeIds(node.der) }
    );
    const d = Math.abs(a - b);
    st.labels[node.id] = `|${a}−${b}| = ${d}`;
    emit(10, `diferencia = abs(alturaIzq − alturaDer) = abs(${a} − ${b}) = ${d}.`);
    if (d > 1) {
      st.states[node.id] = "bad";
      emit(
        11,
        `${d} > 1 ✗ → diferencia <= 1 es false. Por el cortocircuito del operador && se devuelve false SIN evaluar las llamadas recursivas.`
      );
      st.stack.pop();
      return false;
    }
    emit(
      11,
      `diferencia = ${d} <= 1 ✓. El && evalúa de izquierda a derecha (cortocircuito): si esto fuera false, retornaría false sin recursar. Como es true, ahora se comprueba el hijo izquierdo.`
    );
    st.states[node.id] = "stack";
    emit(12, `esEquilibradoRecursivo(nodo->izq) del ${node.val}…`);
    const ok1 = rec(node.izq, node, "izq");
    emit(13, `La izquierda devolvió ${ok1}. Ahora esEquilibradoRecursivo(nodo->der)…`);
    const ok2 = rec(node.der, node, "der");
    st.labels[node.id] = `dif=${d} ✓`;
    st.states[node.id] = "done";
    emit(
      11,
      `return (${d} <= 1) && ${ok1} && ${ok2} = true: el subárbol con raíz ${node.val} está equilibrado.`
    );
    st.stack.pop();
    return true;
  }

  const ok = rec(TREE, null, "");
  emit(2, `esEquilibrado devuelve ${ok} → cout imprime ${ok ? 1 : 0}. Todo el árbol está equilibrado.`);
  return frames;
}

/* ================================================================
   PESTAÑAS
================================================================ */

export const TABS = [
  { key: "plantar", title: "construir / plantar", code: CODE_PLANTAR, gen: genPlantar },
  { key: "pre", title: "recorrerPreOrder", code: codeTraversal("PreOrder"), gen: () => genTraversal("pre") },
  { key: "ino", title: "recorrerInOrder", code: codeTraversal("InOrder"), gen: () => genTraversal("ino") },
  { key: "post", title: "recorrerPostOrder", code: codeTraversal("PostOrder"), gen: () => genTraversal("post") },
  { key: "nodos", title: "numeroNodos", code: CODE_NODOS, gen: genNodos },
  { key: "hojas", title: "numeroHojas", code: CODE_HOJAS, gen: genHojas },
  { key: "altura", title: "altura", code: CODE_ALTURA, gen: genAltura },
  { key: "eq", title: "esEquilibrado", code: CODE_EQ, gen: genEquilibrado },
];

/* ================================================================
   COLORES DE ESTADO DE NODO
================================================================ */

const NODE_STYLE = {
  idle: { fill: "#334155", stroke: "#64748b", text: "#cbd5e1" },
  stack: { fill: "#7c2d12", stroke: "#fb923c", text: "#fed7aa" },
  active: { fill: "#c2410c", stroke: "#fdba74", text: "#ffffff" },
  printed: { fill: "#14532d", stroke: "#4ade80", text: "#bbf7d0" },
  done: { fill: "#14532d", stroke: "#4ade80", text: "#bbf7d0" },
  bad: { fill: "#7f1d1d", stroke: "#f87171", text: "#fecaca" },
};

const LEGEND = [
  { c: NODE_STYLE.idle, t: "No visitado" },
  { c: NODE_STYLE.stack, t: "En la pila (esperando)" },
  { c: NODE_STYLE.active, t: "Ejecutándose ahora" },
  { c: NODE_STYLE.done, t: "Procesado / retornó" },
  { c: { fill: "#4c1d95", stroke: "#a78bfa" }, t: "Medido por alturaRecursivo" },
];

/* ================================================================
   COMPONENTES
================================================================ */

function TreeView({ frame }) {
  const isVisible = (id) => !frame.visible || frame.visible.has(id);
  const edgeOn = (p, c) => (!frame.edges || frame.edges.has(`${p}-${c}`)) && isVisible(p) && isVisible(c);

  return (
    <svg viewBox="0 0 720 410" style={{ width: "100%", height: "100%", display: "block" }}>
      {EDGES.map(([p, c]) => {
        if (!edgeOn(p, c)) return null;
        const a = xy(p), b = xy(c);
        return (
          <line
            key={`${p}-${c}`}
            x1={a.x} y1={a.y} x2={b.x} y2={b.y}
            stroke="#475569" strokeWidth="2.5"
            style={{ transition: "all .3s" }}
          />
        );
      })}

      {/* fantasma de llamada con nullptr */}
      {frame.ghost && (() => {
        const p = xy(frame.ghost.parentId);
        const gx = p.x + (frame.ghost.side === "izq" ? -48 : 48);
        const gy = p.y + 64;
        return (
          <g>
            <line x1={p.x} y1={p.y} x2={gx} y2={gy} stroke="#64748b" strokeWidth="1.5" strokeDasharray="4 4" />
            <circle cx={gx} cy={gy} r="15" fill="none" stroke="#94a3b8" strokeWidth="1.5" strokeDasharray="4 3" />
            <text x={gx} y={gy + 5} textAnchor="middle" fill="#94a3b8" fontSize="14">∅</text>
          </g>
        );
      })()}

      {ALL_IDS.map((id) => {
        if (!isVisible(id)) return null;
        const { x, y } = xy(id);
        const flashed = frame.flash.includes(id);
        const s = NODE_STYLE[frame.states[id]] || NODE_STYLE.idle;
        const fill = flashed ? "#4c1d95" : s.fill;
        const stroke = flashed ? "#a78bfa" : s.stroke;
        const noNum = frame.noNum && frame.noNum.has(id);
        const isActive = frame.states[id] === "active";
        return (
          <g key={id}>
            {isActive && (
              <circle cx={x} cy={y} r="29" fill="none" stroke="#38bdf8" strokeWidth="2.5" opacity="0.9">
                <animate attributeName="r" values="27;31;27" dur="1.2s" repeatCount="indefinite" />
              </circle>
            )}
            <circle
              cx={x} cy={y} r="23"
              fill={fill} stroke={stroke} strokeWidth="2.5"
              style={{ transition: "fill .3s, stroke .3s" }}
            />
            <text
              x={x} y={y + 5.5}
              textAnchor="middle"
              fill={flashed ? "#ddd6fe" : s.text}
              fontSize="15" fontWeight="700" fontFamily="ui-monospace, monospace"
            >
              {noNum ? "?" : valOf(id)}
            </text>
          </g>
        );
      })}

      {/* etiquetas flotantes (retornos de la recursión) */}
      {Object.entries(frame.labels).map(([id, txt]) => {
        if (!isVisible(id)) return null;
        const { x, y } = xy(id);
        const w = txt.length * 7 + 14;
        return (
          <g key={`lbl-${id}`}>
            <rect
              x={x - w / 2} y={y - 56} width={w} height="22" rx="7"
              fill="#0f172a" stroke="#facc15" strokeWidth="1.2" opacity="0.95"
            />
            <text
              x={x} y={y - 41}
              textAnchor="middle" fill="#fde047"
              fontSize="11.5" fontWeight="600" fontFamily="ui-monospace, monospace"
            >
              {txt}
            </text>
          </g>
        );
      })}
    </svg>
  );
}

function CodePanel({ code, line }) {
  const ref = useRef(null);
  useEffect(() => {
    const el = ref.current?.querySelector("[data-active='1']");
    el?.scrollIntoView({ block: "nearest", behavior: "smooth" });
  }, [line, code]);
  return (
    <div ref={ref} className="codebox">
      {code.map((l, i) => (
        <div key={i} data-active={i === line ? "1" : "0"} className={`codeline${i === line ? " hl" : ""}`}>
          <span className="lnum">{i + 1}</span>
          <span style={{ whiteSpace: "pre" }}>{l || " "}</span>
        </div>
      ))}
    </div>
  );
}

function StackPanel({ stack }) {
  return (
    <div className="panelbox">
      <div className="paneltitle">
        <Layers size={14} /> Pila de llamadas {stack.length > 0 && <span className="dim">({stack.length})</span>}
      </div>
      {stack.length === 0 ? (
        <div className="dim" style={{ fontSize: 12, padding: "4px 2px" }}>— vacía —</div>
      ) : (
        [...stack].reverse().map((s, i) => (
          <div key={i} className={`stackframe${i === 0 ? " top" : ""}`}>
            {s} {i === 0 && <span style={{ opacity: 0.7 }}>← tope</span>}
          </div>
        ))
      )}
    </div>
  );
}

function OutputPanel({ output }) {
  return (
    <div className="panelbox">
      <div className="paneltitle">
        <Terminal size={14} /> Salida (cout)
      </div>
      <div style={{ display: "flex", gap: 6, flexWrap: "wrap", minHeight: 26 }}>
        {output.length === 0 ? (
          <span className="dim" style={{ fontSize: 12 }}>— sin salida todavía —</span>
        ) : (
          output.map((v, i) => (
            <span key={i} className="outchip">{v}</span>
          ))
        )}
      </div>
    </div>
  );
}

/* ================================================================
   APP
================================================================ */

export default function App() {
  const [tab, setTab] = useState(0);
  const [idx, setIdx] = useState(0);
  const [playing, setPlaying] = useState(false);
  const [speed, setSpeed] = useState(1);

  const frames = useMemo(() => TABS[tab].gen(), [tab]);
  const frame = frames[Math.min(idx, frames.length - 1)];
  const last = frames.length - 1;

  useEffect(() => {
    setIdx(0);
    setPlaying(false);
  }, [tab]);

  useEffect(() => {
    if (!playing) return;
    const t = setInterval(() => setIdx((i) => Math.min(i + 1, last)), 950 / speed);
    return () => clearInterval(t);
  }, [playing, speed, last]);

  useEffect(() => {
    if (playing && idx >= last) setPlaying(false);
  }, [idx, playing, last]);

  useEffect(() => {
    const onKey = (e) => {
      if (e.key === "ArrowRight") setIdx((i) => Math.min(i + 1, last));
      else if (e.key === "ArrowLeft") setIdx((i) => Math.max(i - 1, 0));
      else if (e.key === " ") {
        e.preventDefault();
        setPlaying((p) => !p);
      }
    };
    window.addEventListener("keydown", onKey);
    return () => window.removeEventListener("keydown", onKey);
  }, [last]);

  return (
    <div className="app">
      <style>{CSS}</style>

      <header className="header">
        <TreePine size={22} color="#4ade80" />
        <div>
          <div style={{ fontWeight: 800, fontSize: 16 }}>Simulador de Árbol Binario</div>
          <div className="dim" style={{ fontSize: 12 }}>
            Ejecución paso a paso de FuncionesArbolBinario.cpp — árbol de main.cpp
          </div>
        </div>
      </header>

      <nav className="tabs">
        {TABS.map((t, i) => (
          <button key={t.key} className={`tab${i === tab ? " on" : ""}`} onClick={() => setTab(i)}>
            {t.title}
          </button>
        ))}
      </nav>

      <main className="grid">
        {/* ---------- izquierda: árbol ---------- */}
        <section className="left">
          <div className="treewrap">
            <TreeView frame={frame} />
          </div>

          <div className="desc">{frame.desc}</div>

          <div className="legend">
            {LEGEND.map((l, i) => (
              <span key={i} className="legitem">
                <span className="dot" style={{ background: l.c.fill, borderColor: l.c.stroke }} />
                {l.t}
              </span>
            ))}
          </div>
        </section>

        {/* ---------- derecha: código + controles ---------- */}
        <section className="right">
          <div className="paneltitle" style={{ marginBottom: 6 }}>
            <Code2 size={14} /> Seguimiento de código C++ — {TABS[tab].title}
          </div>
          <CodePanel code={TABS[tab].code} line={frame.line} />

          <div className="controls">
            <button className="btn" onClick={() => { setPlaying(false); setIdx(0); }} title="Reiniciar">
              <RotateCcw size={17} />
            </button>
            <button
              className="btn"
              onClick={() => { setPlaying(false); setIdx((i) => Math.max(i - 1, 0)); }}
              disabled={idx === 0}
              title="Paso anterior (←)"
            >
              <ChevronLeft size={19} />
            </button>
            <button
              className="btn play"
              onClick={() => setPlaying((p) => (idx >= last ? p : !p))}
              disabled={idx >= last}
              title="Reproducir / Pausar (espacio)"
            >
              {playing ? <Pause size={19} /> : <Play size={19} />}
            </button>
            <button
              className="btn"
              onClick={() => { setPlaying(false); setIdx((i) => Math.min(i + 1, last)); }}
              disabled={idx >= last}
              title="Siguiente paso (→)"
            >
              <ChevronRight size={19} />
            </button>
            <span className="stepcount">
              Paso {idx + 1} / {frames.length}
            </span>
            <span className="speed">
              <Gauge size={14} />
              <select value={speed} onChange={(e) => setSpeed(+e.target.value)}>
                <option value={0.5}>0.5×</option>
                <option value={1}>1×</option>
                <option value={2}>2×</option>
                <option value={4}>4×</option>
              </select>
            </span>
          </div>

          <input
            type="range"
            min={0}
            max={last}
            value={idx}
            onChange={(e) => { setPlaying(false); setIdx(+e.target.value); }}
            className="slider"
          />

          <StackPanel stack={frame.stack} />
          <OutputPanel output={frame.output} />
        </section>
      </main>
    </div>
  );
}

/* ================================================================
   ESTILOS
================================================================ */

const CSS = `
* { box-sizing: border-box; }
body { margin: 0; background: #0b1220; }
.app {
  min-height: 100vh; background: #0b1220; color: #e2e8f0;
  font-family: ui-sans-serif, system-ui, -apple-system, "Segoe UI", sans-serif;
  display: flex; flex-direction: column;
}
.header {
  display: flex; align-items: center; gap: 12px;
  padding: 14px 22px; border-bottom: 1px solid #1e293b;
}
.dim { color: #64748b; }
.tabs {
  display: flex; gap: 6px; flex-wrap: wrap;
  padding: 10px 22px; border-bottom: 1px solid #1e293b;
}
.tab {
  background: #1e293b; color: #94a3b8; border: 1px solid #334155;
  border-radius: 8px; padding: 7px 13px; font-size: 13px; font-weight: 600;
  cursor: pointer; font-family: ui-monospace, monospace; transition: all .15s;
}
.tab:hover { color: #e2e8f0; border-color: #475569; }
.tab.on { background: #0c4a6e; color: #7dd3fc; border-color: #0284c7; }
.grid {
  flex: 1; display: grid; grid-template-columns: minmax(0, 1.25fr) minmax(0, 1fr);
  gap: 18px; padding: 18px 22px; align-items: start;
}
@media (max-width: 980px) { .grid { grid-template-columns: 1fr; } }
.left { display: flex; flex-direction: column; gap: 12px; }
.treewrap {
  background: #0f172a; border: 1px solid #1e293b; border-radius: 14px;
  padding: 8px; min-height: 380px;
}
.desc {
  background: #082f49; border: 1px solid #0369a1; border-radius: 12px;
  padding: 12px 16px; font-size: 14.5px; line-height: 1.55; color: #bae6fd;
  min-height: 64px;
}
.legend { display: flex; gap: 14px; flex-wrap: wrap; font-size: 12px; color: #94a3b8; }
.legitem { display: inline-flex; align-items: center; gap: 6px; }
.dot {
  width: 13px; height: 13px; border-radius: 50%;
  display: inline-block; border: 2px solid;
}
.right { display: flex; flex-direction: column; gap: 12px; }
.codebox {
  background: #0f172a; border: 1px solid #1e293b; border-radius: 12px;
  padding: 10px 0; font-family: ui-monospace, SFMono-Regular, Menlo, monospace;
  font-size: 12.5px; line-height: 1.65; overflow: auto; max-height: 360px;
}
.codeline { display: flex; padding: 0 12px; color: #94a3b8; border-left: 3px solid transparent; }
.codeline.hl {
  background: #422006; color: #fef3c7; border-left-color: #f59e0b;
}
.lnum {
  width: 30px; flex-shrink: 0; text-align: right; margin-right: 14px;
  color: #475569; user-select: none;
}
.codeline.hl .lnum { color: #b45309; }
.controls { display: flex; align-items: center; gap: 8px; flex-wrap: wrap; }
.btn {
  background: #1e293b; border: 1px solid #334155; color: #e2e8f0;
  border-radius: 9px; width: 40px; height: 38px; cursor: pointer;
  display: inline-flex; align-items: center; justify-content: center;
  transition: all .15s;
}
.btn:hover:not(:disabled) { background: #334155; }
.btn:disabled { opacity: 0.35; cursor: default; }
.btn.play { background: #065f46; border-color: #059669; }
.btn.play:hover:not(:disabled) { background: #047857; }
.stepcount { font-size: 13px; color: #94a3b8; font-weight: 600; margin-left: 4px; }
.speed { display: inline-flex; align-items: center; gap: 5px; margin-left: auto; color: #64748b; }
.speed select {
  background: #1e293b; color: #e2e8f0; border: 1px solid #334155;
  border-radius: 7px; padding: 4px 6px; font-size: 12px;
}
.slider { width: 100%; accent-color: #0ea5e9; cursor: pointer; }
.panelbox {
  background: #0f172a; border: 1px solid #1e293b; border-radius: 12px;
  padding: 10px 14px;
}
.paneltitle {
  display: flex; align-items: center; gap: 7px;
  font-size: 12px; font-weight: 700; text-transform: uppercase;
  letter-spacing: 0.06em; color: #7dd3fc; margin-bottom: 7px;
}
.stackframe {
  font-family: ui-monospace, monospace; font-size: 12px;
  background: #1e293b; border: 1px solid #334155; color: #cbd5e1;
  border-radius: 7px; padding: 4px 10px; margin-bottom: 4px;
}
.stackframe.top { background: #431407; border-color: #ea580c; color: #fdba74; }
.outchip {
  font-family: ui-monospace, monospace; font-size: 13px; font-weight: 700;
  background: #14532d; border: 1px solid #22c55e; color: #bbf7d0;
  border-radius: 7px; padding: 3px 10px;
}
`;
