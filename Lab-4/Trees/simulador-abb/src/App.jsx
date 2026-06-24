import React, { useState, useEffect, useMemo, useRef } from "react";
import {
  Play,
  Pause,
  RotateCcw,
  ChevronLeft,
  ChevronRight,
  Network,
  Code2,
  Terminal,
  Gauge,
  Target,
  Plus,
  Search,
  Trash2,
  ArrowDownToLine,
  Scale,
  ListTree,
} from "lucide-react";

/* ================================================================
   SIMULADOR INTERACTIVO — Árbol Binario de Búsqueda (ABB)
   Un único árbol persistente sobre el que el usuario escribe un
   número y elige la operación. Visualiza las funciones propias
   del ABB (FuncionesArbolBinarioBusqueda.cpp):
        insertar / insertarRecursivo  (+ comparaElementos)
        buscar / buscarRecursivo
        minimoArbol
        eliminar / eliminarRecursivo   (0 hijos, 1 hijo, 2 hijos)
   El árbol crece y cambia, por eso el layout se recalcula en cada
   frame a partir de la estructura del árbol (no posiciones fijas).
================================================================ */

/* ---- comparaElementos del C++ ----
   comparaElementos(elemA, elemB):  0 si iguales, -1 si A<B, 1 si A>B.
   Siempre se llama con elemA = dato del nodo, elemB = dato buscado.
      cmp ==  1  -> el nodo es MAYOR  -> ir a la izquierda
      cmp == -1  -> el nodo es MENOR  -> ir a la derecha
      cmp ==  0  -> iguales                                            */
const compara = (a, b) => (a === b ? 0 : a < b ? -1 : 1);

let UID = 0;
const node = (val) => ({ id: "u" + UID++, val, izq: null, der: null });

function insertPlain(root, val) {
  if (!root) return node(val);
  const c = compara(root.val, val);
  if (c === 1) root.izq = insertPlain(root.izq, val);
  else if (c === -1) root.der = insertPlain(root.der, val);
  return root;
}
function buildTree(seq) {
  let r = null;
  for (const v of seq) r = insertPlain(r, v);
  return r;
}
const SEQ = [50, 30, 70, 20, 40, 80, 10];
const inorder = (n) => (n ? [...inorder(n.izq), n.val, ...inorder(n.der)] : []);

/* ================================================================
   LAYOUT — posición (columna in-order, profundidad) de cada nodo
================================================================ */
function layout(root) {
  const pos = {};
  let col = 0;
  let maxDepth = 0;
  (function walk(n, d) {
    if (!n) return;
    walk(n.izq, d + 1);
    pos[n.id] = [col++, d];
    maxDepth = Math.max(maxDepth, d);
    walk(n.der, d + 1);
  })(root, 0);
  return { pos, nCols: col, maxDepth };
}

/* ================================================================
   BLOQUES DE CÓDIGO C++  (FuncionesArbolBinarioBusqueda.cpp)
================================================================ */
const CODE_INSERTAR = [
  "void insertar(ArbolBinarioBusqueda &arbol, const Elemento &elemento) {",
  "    insertarRecursivo(arbol.raiz, elemento);",
  "}",
  "",
  "void insertarRecursivo(NodoABB *&raiz, const Elemento &elemento) {",
  "    if (esNodoVacio(raiz)) {",
  "        plantarNodoRecursivo(raiz, nullptr, elemento, nullptr);",
  "    } else {",
  "        int cmp = comparaElementos(raiz->elemento.dato, elemento.dato);",
  "        if (cmp == 1) {            // raiz mayor: a la izquierda",
  "            insertarRecursivo(raiz->izq, elemento);",
  "        } else if (cmp == -1) {    // raiz menor: a la derecha",
  "            insertarRecursivo(raiz->der, elemento);",
  "        } else {                   // iguales: ya existe",
  '            cout << "El elemento ya se encuentra en el arbol";',
  "        }",
  "    }",
  "}",
];

const CODE_COMPARA = [
  "int comparaElementos(int elemA, int elemB) {",
  "    if (elemA == elemB)      return 0;",
  "    else if (elemA <  elemB) return -1;",
  "    else                     return 1;",
  "}",
];

const CODE_BUSCAR = [
  "bool buscar(const ArbolBinarioBusqueda &arbol, const Elemento &elemento) {",
  "    return buscarRecursivo(arbol.raiz, elemento);",
  "}",
  "",
  "bool buscarRecursivo(NodoABB *nodo, const Elemento &elemento) {",
  "    if (esNodoVacio(nodo)) {",
  "        return false;",
  "    } else {",
  "        int cmp = comparaElementos(nodo->elemento.dato, elemento.dato);",
  "        if (cmp == 0) {",
  "            return true;",
  "        } else if (cmp == 1) {",
  "            return buscarRecursivo(nodo->izq, elemento);",
  "        } else {",
  "            return buscarRecursivo(nodo->der, elemento);",
  "        }",
  "    }",
  "}",
];

const CODE_MINIMO = [
  "NodoABB *minimoArbol(NodoABB *nodo) {",
  "    if (esNodoVacio(nodo)) {",
  "        return nodo;",
  "    } else if (esNodoVacio(nodo->izq)) {",
  "        return nodo;          // sin hijo izquierdo -> es el minimo",
  "    } else {",
  "        return minimoArbol(nodo->izq);   // seguir a la izquierda",
  "    }",
  "}",
];

const CODE_ELIMINAR = [
  "void eliminar(ArbolBinarioBusqueda &arbol, const Elemento &elemento) {",
  "    arbol.raiz = eliminarRecursivo(arbol.raiz, elemento);",
  "}",
  "",
  "NodoABB *eliminarRecursivo(NodoABB *nodo, const Elemento &elemento) {",
  "    if (esNodoVacio(nodo)) return nodo;",
  "    int cmp = comparaElementos(nodo->elemento.dato, elemento.dato);",
  "    if (cmp == 1) {",
  "        nodo->izq = eliminarRecursivo(nodo->izq, elemento);",
  "    } else if (cmp == -1) {",
  "        nodo->der = eliminarRecursivo(nodo->der, elemento);",
  "    } else if (esNodoVacio(nodo->izq)) {       // 0 o 1 hijo (der)",
  "        NodoABB *hijo = nodo->der;  delete nodo;  return hijo;",
  "    } else if (esNodoVacio(nodo->der)) {       // 1 hijo (izq)",
  "        NodoABB *hijo = nodo->izq;  delete nodo;  return hijo;",
  "    } else {                                    // 2 hijos",
  "        NodoABB *minNodo = minimoArbol(nodo->der);",
  "        nodo->elemento = minNodo->elemento;",
  "        nodo->der = eliminarRecursivo(nodo->der, minNodo->elemento);",
  "    }",
  "    return nodo;",
  "}",
];

/* ================================================================
   BUILDER de frames — cada frame clona el árbol vivo (st.root)
================================================================ */
function clone(n) {
  return n ? { id: n.id, val: n.val, izq: clone(n.izq), der: clone(n.der) } : null;
}
function markTree(root, states) {
  (function walk(n) {
    if (!n) return;
    states[n.id] = "tree";
    walk(n.izq);
    walk(n.der);
  })(root);
}
function builder(initialRoot = null) {
  const frames = [];
  const st = { root: initialRoot, states: {}, labels: {}, output: [], target: null };
  const emit = (line, desc, extra = {}) =>
    frames.push({
      line,
      desc,
      tree: clone(st.root),
      states: { ...st.states },
      labels: { ...st.labels },
      ghost: extra.ghost || null,
      flash: extra.flash || [],
      target: extra.target ?? st.target ?? null,
      result: extra.result ?? null,
    });
  return { frames, st, emit };
}

/* ================================================================
   OPERACIONES — cada una recibe el árbol actual (root) y un valor.
   Devuelve { frames, root } con el árbol resultante (insertar /
   eliminar lo modifican; buscar / minimo lo dejan igual).
================================================================ */

function runInsertar(root, val) {
  const { frames, st, emit } = builder(clone(root));
  st.target = val;
  markTree(st.root, st.states);
  emit(1, `insertar(${val}): se llama a insertarRecursivo pasando arbol.raiz por referencia.`, {
    target: val,
  });

  insertRec(st.root, val, null, null);

  function insertRec(cur, value, parent, side) {
    if (cur === null) {
      emit(
        5,
        parent === null
          ? `esNodoVacio(raiz) es true: el árbol está vacío. Aquí se planta ${value}, que será la raíz.`
          : `esNodoVacio(raiz) es true: llegamos a un hueco (hijo ${side === "izq" ? "izquierdo" : "derecho"} de ${parent.val}). Aquí se planta ${value}.`,
        parent ? { ghost: { parentId: parent.id, side }, target: value } : { target: value }
      );
      const nuevo = node(value);
      if (parent === null) st.root = nuevo;
      else parent[side] = nuevo;
      st.states[nuevo.id] = "found";
      emit(6, `plantarNodoRecursivo crea el nodo ${value} con ambos hijos en nullptr y lo enlaza en su sitio.`, {
        target: value,
      });
      return;
    }
    st.states[cur.id] = "active";
    const c = compara(cur.val, value);
    st.labels[cur.id] = `cmp=${c}`;
    emit(
      8,
      `cmp = comparaElementos(${cur.val}, ${value}) = ${c} → ${
        c === 1
          ? `el nodo (${cur.val}) es MAYOR que ${value}.`
          : c === -1
          ? `el nodo (${cur.val}) es MENOR que ${value}.`
          : `son IGUALES.`
      }`,
      { target: value }
    );
    if (c === 1) {
      emit(10, `cmp == 1 → ${value} debe ir a la IZQUIERDA de ${cur.val}. Bajamos por raiz->izq.`, { target: value });
      st.states[cur.id] = "path";
      delete st.labels[cur.id];
      insertRec(cur.izq, value, cur, "izq");
    } else if (c === -1) {
      emit(12, `cmp == -1 → ${value} debe ir a la DERECHA de ${cur.val}. Bajamos por raiz->der.`, { target: value });
      st.states[cur.id] = "path";
      delete st.labels[cur.id];
      insertRec(cur.der, value, cur, "der");
    } else {
      st.states[cur.id] = "bad";
      emit(15, `cmp == 0 → ${value} ya existe. No se inserta (un ABB no admite duplicados).`, {
        target: value,
        result: "duplicado",
      });
    }
  }
  emit(null, `Listo. InOrder del árbol: [${inorder(st.root).join("  ")}] (siempre queda ordenado).`, {
    target: val,
  });
  return { frames, root: st.root };
}

function runBuscar(root, val) {
  const { frames, st, emit } = builder(clone(root));
  st.target = val;
  markTree(st.root, st.states);
  emit(1, `buscar(${val}): se llama a buscarRecursivo con la raíz del árbol.`, { target: val });

  const res = rec(st.root, val, null, null);

  function rec(cur, value, parent, side) {
    if (cur === null) {
      emit(
        6,
        parent === null
          ? `esNodoVacio(nodo) es true: el árbol está vacío → return false.`
          : `esNodoVacio(nodo) es true: caímos en un nullptr sin encontrar ${value} → return false.`,
        { ghost: parent ? { parentId: parent.id, side } : null, target: value, result: false }
      );
      return false;
    }
    st.states[cur.id] = "active";
    const c = compara(cur.val, value);
    st.labels[cur.id] = `cmp=${c}`;
    emit(8, `cmp = comparaElementos(${cur.val}, ${value}) = ${c}.`, { target: value });
    if (c === 0) {
      st.states[cur.id] = "found";
      delete st.labels[cur.id];
      emit(10, `cmp == 0 → ¡${value} encontrado en el nodo ${cur.val}! return true.`, { target: value, result: true });
      return true;
    }
    if (c === 1) {
      emit(11, `cmp == 1 → ${cur.val} es mayor que ${value}. ${value} sólo puede estar a la IZQUIERDA. Bajamos por nodo->izq.`, {
        target: value,
      });
      st.states[cur.id] = "path";
      delete st.labels[cur.id];
      return rec(cur.izq, value, cur, "izq");
    }
    emit(13, `cmp == -1 → ${cur.val} es menor que ${value}. ${value} sólo puede estar a la DERECHA. Bajamos por nodo->der.`, {
      target: value,
    });
    st.states[cur.id] = "path";
    delete st.labels[cur.id];
    return rec(cur.der, value, cur, "der");
  }

  emit(
    2,
    res
      ? `buscar devuelve true. Sólo se recorrió el camino hasta ${val}, no todo el árbol: el ABB descarta medio árbol en cada comparación.`
      : `buscar devuelve false: ${val} no está en el árbol.`,
    { target: val, result: res }
  );
  return { frames, root };
}

function runMinimo(root) {
  const { frames, st, emit } = builder(clone(root));
  markTree(st.root, st.states);
  if (!st.root) {
    emit(2, "minimoArbol: el árbol está vacío (esNodoVacio es true) → devuelve nullptr. No hay mínimo.", {
      result: "—",
    });
    return { frames, root };
  }
  emit(1, "minimoArbol(raiz): en un ABB el menor valor es el nodo más a la izquierda. Bajamos siempre por nodo->izq.");
  const min = rec(st.root);
  function rec(cur) {
    st.states[cur.id] = "active";
    emit(2, `esNodoVacio(${cur.val}) es false.`);
    if (!cur.izq) {
      st.states[cur.id] = "found";
      emit(4, `esNodoVacio(nodo->izq) es true: ${cur.val} no tiene hijo izquierdo → es el MÍNIMO. return ${cur.val}.`, {
        result: cur.val,
      });
      return cur;
    }
    emit(6, `${cur.val} sí tiene hijo izquierdo (${cur.izq.val}) → todavía hay valores menores. minimoArbol(nodo->izq).`);
    st.states[cur.id] = "path";
    return rec(cur.izq);
  }
  emit(1, `El mínimo del árbol es ${min.val}. Esta función es la pieza clave para eliminar un nodo con dos hijos (su sucesor inorden).`, {
    result: min.val,
  });
  return { frames, root };
}

function runEliminar(root, val) {
  const { frames, st, emit } = builder(clone(root));
  st.target = val;
  markTree(st.root, st.states);
  emit(1, `eliminar(${val}): arbol.raiz = eliminarRecursivo(arbol.raiz, ${val}). El return reconstruye los enlaces al subir.`, {
    target: val,
  });

  let found = true;

  function setChild(parent, side, child) {
    if (parent === null) st.root = child;
    else parent[side] = child;
  }

  rec(st.root, val, null, null);

  function rec(cur, value, parent, side) {
    if (cur === null) {
      found = false;
      emit(5, `esNodoVacio(nodo) es true: ${value} no está en el árbol, no hay nada que eliminar. return nodo (nullptr).`, {
        ghost: parent ? { parentId: parent.id, side } : null,
        target: value,
        result: false,
      });
      return;
    }
    st.states[cur.id] = "active";
    const c = compara(cur.val, value);
    st.labels[cur.id] = `cmp=${c}`;
    emit(6, `cmp = comparaElementos(${cur.val}, ${value}) = ${c}.`, { target: value });

    if (c === 1) {
      emit(7, `cmp == 1 → ${value} está a la IZQUIERDA. nodo->izq = eliminarRecursivo(nodo->izq, ${value}).`, { target: value });
      st.states[cur.id] = "path";
      delete st.labels[cur.id];
      rec(cur.izq, value, cur, "izq");
      return;
    }
    if (c === -1) {
      emit(9, `cmp == -1 → ${value} está a la DERECHA. nodo->der = eliminarRecursivo(nodo->der, ${value}).`, { target: value });
      st.states[cur.id] = "path";
      delete st.labels[cur.id];
      rec(cur.der, value, cur, "der");
      return;
    }

    // encontrado
    st.states[cur.id] = "bad";
    delete st.labels[cur.id];
    emit(6, `cmp == 0 → ¡nodo ${cur.val} encontrado! Se decide el caso según sus hijos.`, { target: value });

    if (!cur.izq) {
      const hijo = cur.der;
      emit(
        11,
        hijo
          ? `Caso 1 hijo: esNodoVacio(nodo->izq) es true. hijo = nodo->der (${hijo.val}); delete nodo; return hijo, que ocupa su lugar.`
          : `Caso hoja: nodo->izq y nodo->der son nullptr. hijo = nullptr; delete nodo; return nullptr: el nodo desaparece.`,
        { target: value }
      );
      setChild(parent, side, hijo);
      emit(11, hijo ? `${hijo.val} queda enlazado donde estaba ${cur.val}.` : `${cur.val} eliminado.`, { target: value });
      return;
    }
    if (!cur.der) {
      const hijo = cur.izq;
      emit(13, `Caso 1 hijo: nodo->izq existe pero esNodoVacio(nodo->der) es true. hijo = nodo->izq (${hijo.val}); delete nodo; return hijo.`, {
        target: value,
      });
      setChild(parent, side, hijo);
      emit(13, `${hijo.val} sube y ocupa el lugar de ${cur.val}.`, { target: value });
      return;
    }

    // 2 hijos
    emit(15, `Caso 2 hijos: ${cur.val} tiene ambos hijos. Se busca su SUCESOR inorden = minimoArbol(nodo->der).`, { target: value });
    const min = minimo(cur.der);
    emit(16, `minimoArbol(nodo->der) devolvió ${min.val}: el menor valor mayor que ${cur.val}. Se COPIA su valor dentro del nodo.`, {
      target: value,
      flash: [min.id],
    });
    cur.val = min.val;
    st.states[cur.id] = "active";
    emit(16, `El nodo ahora contiene ${min.val}. Pero ${min.val} aparece dos veces: hay que borrar el original del subárbol derecho.`, {
      target: min.val,
      flash: [min.id],
    });
    emit(17, `nodo->der = eliminarRecursivo(nodo->der, ${min.val}): se elimina el sucesor duplicado (tiene 0 o 1 hijo, caso fácil).`, {
      target: min.val,
    });
    st.states[cur.id] = "path";
    rec(cur.der, min.val, cur, "der");
    return;
  }

  function minimo(cur) {
    st.states[cur.id] = "min";
    emit(15, `minimoArbol: bajando por la izquierda desde ${cur.val}…`, { flash: [cur.id] });
    if (!cur.izq) {
      emit(15, `${cur.val} no tiene hijo izquierdo → es el sucesor.`, { flash: [cur.id] });
      return cur;
    }
    return minimo(cur.izq);
  }

  emit(
    2,
    found
      ? `eliminar(${val}) terminado. InOrder: [${inorder(st.root).join("  ")}] — el árbol sigue siendo un ABB válido (ordenado).`
      : `${val} no estaba en el árbol: no cambió nada.`,
    { target: null, result: found ? undefined : false }
  );
  return { frames, root: st.root };
}

function runCompara() {
  const { frames, st, emit } = builder(null);
  const casos = [
    [50, 50, 0, "iguales: el elemento ya existe / es el buscado."],
    [50, 30, 1, "elemA (50) es MAYOR → return 1 → bajar a la IZQUIERDA."],
    [50, 80, -1, "elemA (50) es MENOR → return -1 → bajar a la DERECHA."],
  ];
  emit(null, "comparaElementos es la 'brújula' del ABB: con un entero (-1, 0 ó 1) decide a qué lado bajar. Sus tres resultados:");
  for (const [a, b, r, txt] of casos) {
    if (r === 0) emit(2, `comparaElementos(${a}, ${b}): elemA == elemB → return 0. ${txt}`, { result: "cmp = 0" });
    else if (r === -1) emit(3, `comparaElementos(${a}, ${b}): elemA < elemB → return -1. ${txt}`, { result: "cmp = -1" });
    else emit(4, `comparaElementos(${a}, ${b}): si no es == ni < → return 1. ${txt}`, { result: "cmp = 1" });
  }
  emit(null, "Resumen: cmp==1 → izquierda · cmp==-1 → derecha · cmp==0 → encontrado/duplicado. Insertar, buscar y eliminar giran en torno a este resultado.");
  return { frames, root: null };
}

function runStatic(root, desc) {
  const { frames, st, emit } = builder(clone(root));
  markTree(st.root, st.states);
  emit(null, desc);
  return { frames, root };
}

/* ================================================================
   COLORES DE ESTADO
================================================================ */
const NODE_STYLE = {
  tree: { fill: "#1e293b", stroke: "#475569", text: "#cbd5e1" },
  path: { fill: "#1e3a8a", stroke: "#60a5fa", text: "#dbeafe" },
  active: { fill: "#c2410c", stroke: "#fdba74", text: "#ffffff" },
  found: { fill: "#14532d", stroke: "#4ade80", text: "#bbf7d0" },
  done: { fill: "#14532d", stroke: "#4ade80", text: "#bbf7d0" },
  bad: { fill: "#7f1d1d", stroke: "#f87171", text: "#fecaca" },
  min: { fill: "#4c1d95", stroke: "#a78bfa", text: "#ddd6fe" },
};
const LEGEND = [
  { c: NODE_STYLE.tree, t: "Nodo del árbol" },
  { c: NODE_STYLE.path, t: "Camino recorrido" },
  { c: NODE_STYLE.active, t: "Comparando ahora" },
  { c: NODE_STYLE.found, t: "Encontrado / insertado" },
  { c: NODE_STYLE.bad, t: "Nodo a eliminar" },
  { c: NODE_STYLE.min, t: "minimoArbol (sucesor)" },
];

/* ================================================================
   VISTA DEL ÁRBOL
================================================================ */
function TreeView({ frame }) {
  const { pos, nCols, maxDepth } = useMemo(() => layout(frame.tree), [frame.tree]);
  const COLW = 86;
  const ROWH = 96;
  const padX = 44;
  const padY = 50;
  const width = Math.max(360, padX * 2 + Math.max(0, nCols - 1) * COLW);
  const height = padY * 2 + maxDepth * ROWH;
  const xy = (id) => {
    const [col, d] = pos[id];
    return { x: padX + col * COLW, y: padY + d * ROWH };
  };

  const nodes = [];
  const edges = [];
  (function walk(n) {
    if (!n) return;
    nodes.push(n);
    for (const side of ["izq", "der"]) if (n[side]) edges.push([n.id, n[side].id]);
    walk(n.izq);
    walk(n.der);
  })(frame.tree);

  return (
    <svg viewBox={`0 0 ${width} ${height}`} style={{ width: "100%", height: "100%", display: "block" }} preserveAspectRatio="xMidYMid meet">
      {nodes.length === 0 && (
        <text x={width / 2} y={height / 2} textAnchor="middle" fill="#475569" fontSize="16" fontFamily="ui-monospace, monospace">
          árbol vacío (arbol.raiz == nullptr)
        </text>
      )}

      {frame.target != null && (
        <g>
          <rect x={width - 132} y={10} width={122} height={30} rx={9} fill="#0c4a6e" stroke="#0284c7" />
          <text x={width - 120} y={30} fill="#7dd3fc" fontSize="13" fontWeight="700" fontFamily="ui-monospace, monospace">
            objetivo: {frame.target}
          </text>
        </g>
      )}

      {edges.map(([p, c]) => {
        const a = xy(p), b = xy(c);
        return <line key={`${p}-${c}`} x1={a.x} y1={a.y} x2={b.x} y2={b.y} stroke="#475569" strokeWidth="2.5" style={{ transition: "all .3s" }} />;
      })}

      {frame.ghost &&
        pos[frame.ghost.parentId] &&
        (() => {
          const p = xy(frame.ghost.parentId);
          const gx = p.x + (frame.ghost.side === "izq" ? -42 : 42);
          const gy = p.y + 58;
          return (
            <g>
              <line x1={p.x} y1={p.y} x2={gx} y2={gy} stroke="#64748b" strokeWidth="1.5" strokeDasharray="4 4" />
              <circle cx={gx} cy={gy} r="15" fill="none" stroke="#94a3b8" strokeWidth="1.5" strokeDasharray="4 3" />
              <text x={gx} y={gy + 5} textAnchor="middle" fill="#94a3b8" fontSize="14">∅</text>
            </g>
          );
        })()}

      {nodes.map((n) => {
        const { x, y } = xy(n.id);
        const flashed = frame.flash.includes(n.id);
        const s = NODE_STYLE[frame.states[n.id]] || NODE_STYLE.tree;
        const fill = flashed ? "#4c1d95" : s.fill;
        const stroke = flashed ? "#a78bfa" : s.stroke;
        const ring = frame.states[n.id] === "active" || frame.states[n.id] === "bad";
        return (
          <g key={n.id}>
            {ring && (
              <circle cx={x} cy={y} r="29" fill="none" stroke={frame.states[n.id] === "bad" ? "#f87171" : "#38bdf8"} strokeWidth="2.5" opacity="0.9">
                <animate attributeName="r" values="27;31;27" dur="1.2s" repeatCount="indefinite" />
              </circle>
            )}
            <circle cx={x} cy={y} r="23" fill={fill} stroke={stroke} strokeWidth="2.5" style={{ transition: "fill .3s, stroke .3s" }} />
            <text x={x} y={y + 5.5} textAnchor="middle" fill={flashed ? "#ddd6fe" : s.text} fontSize="15" fontWeight="700" fontFamily="ui-monospace, monospace">
              {n.val}
            </text>
          </g>
        );
      })}

      {Object.entries(frame.labels).map(([id, txt]) => {
        if (!pos[id]) return null;
        const { x, y } = xy(id);
        const w = txt.length * 7 + 14;
        return (
          <g key={`lbl-${id}`}>
            <rect x={x - w / 2} y={y - 54} width={w} height="22" rx="7" fill="#0f172a" stroke="#facc15" strokeWidth="1.2" opacity="0.95" />
            <text x={x} y={y - 39} textAnchor="middle" fill="#fde047" fontSize="11.5" fontWeight="600" fontFamily="ui-monospace, monospace">
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

/* ================================================================
   APP
================================================================ */
const OPS = {
  insertar: { title: "insertar", code: CODE_INSERTAR },
  buscar: { title: "buscar", code: CODE_BUSCAR },
  eliminar: { title: "eliminar", code: CODE_ELIMINAR },
  minimo: { title: "minimoArbol", code: CODE_MINIMO },
  compara: { title: "comparaElementos", code: CODE_COMPARA },
  inicio: { title: "insertar", code: CODE_INSERTAR },
};

export default function App() {
  const [tree, setTree] = useState(() => buildTree(SEQ));
  const [opName, setOpName] = useState("inicio");
  const [frames, setFrames] = useState(() => runStatic(buildTree(SEQ), "Este es el ABB actual. Escribe un número arriba y elige una operación: Insertar, Buscar o Eliminar. El árbol se mantiene entre operaciones.").frames);
  const [idx, setIdx] = useState(0);
  const [playing, setPlaying] = useState(false);
  const [speed, setSpeed] = useState(1);
  const [val, setVal] = useState("");

  const frame = frames[Math.min(idx, frames.length - 1)];
  const last = frames.length - 1;
  const op = OPS[opName];

  const parseVal = () => {
    const n = parseInt(val, 10);
    return Number.isInteger(n) && String(n) === val.trim() ? n : null;
  };
  const num = parseVal();

  const startOp = (name, result) => {
    setOpName(name);
    setFrames(result.frames);
    setIdx(0);
    setPlaying(true);
  };

  const doInsertar = () => {
    if (num == null) return;
    const r = runInsertar(tree, num);
    setTree(r.root);
    startOp("insertar", r);
    setVal("");
  };
  const doBuscar = () => {
    if (num == null) return;
    startOp("buscar", runBuscar(tree, num));
  };
  const doEliminar = () => {
    if (num == null) return;
    const r = runEliminar(tree, num);
    setTree(r.root);
    startOp("eliminar", r);
    setVal("");
  };
  const doMinimo = () => startOp("minimo", runMinimo(tree));
  const doCompara = () => startOp("compara", runCompara());
  const doEjemplo = () => {
    const t = buildTree(SEQ);
    setTree(t);
    setOpName("inicio");
    setFrames(runStatic(t, "Árbol de ejemplo cargado (50, 30, 70, 20, 40, 80, 10).").frames);
    setIdx(0);
    setPlaying(false);
  };
  const doVaciar = () => {
    setTree(null);
    setOpName("inicio");
    setFrames(runStatic(null, "Árbol vaciado. Inserta valores para construir tu propio ABB.").frames);
    setIdx(0);
    setPlaying(false);
  };

  useEffect(() => {
    if (!playing) return;
    const t = setInterval(() => setIdx((i) => Math.min(i + 1, last)), 1000 / speed);
    return () => clearInterval(t);
  }, [playing, speed, last]);

  useEffect(() => {
    if (playing && idx >= last) setPlaying(false);
  }, [idx, playing, last]);

  useEffect(() => {
    const onKey = (e) => {
      if (e.target.tagName === "INPUT") return;
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

  const orden = inorder(tree);

  return (
    <div className="app">
      <style>{CSS}</style>

      <header className="header">
        <Network size={22} color="#38bdf8" />
        <div>
          <div style={{ fontWeight: 800, fontSize: 16 }}>Simulador interactivo de Árbol Binario de Búsqueda (ABB)</div>
          <div className="dim" style={{ fontSize: 12 }}>
            FuncionesArbolBinarioBusqueda.cpp — escribe un número y opera sobre el árbol
          </div>
        </div>
      </header>

      {/* barra de operaciones */}
      <div className="opbar">
        <input
          className="numinput"
          type="number"
          placeholder="nº"
          value={val}
          onChange={(e) => setVal(e.target.value)}
          onKeyDown={(e) => { if (e.key === "Enter") doInsertar(); }}
        />
        <button className="opbtn ins" onClick={doInsertar} disabled={num == null} title="Insertar el número (Enter)">
          <Plus size={15} /> Insertar
        </button>
        <button className="opbtn bus" onClick={doBuscar} disabled={num == null} title="Buscar el número">
          <Search size={15} /> Buscar
        </button>
        <button className="opbtn eli" onClick={doEliminar} disabled={num == null} title="Eliminar el número">
          <Trash2 size={15} /> Eliminar
        </button>
        <span className="opsep" />
        <button className="opbtn alt" onClick={doMinimo} title="minimoArbol">
          <ArrowDownToLine size={15} /> Mínimo
        </button>
        <button className="opbtn alt" onClick={doCompara} title="comparaElementos">
          <Scale size={15} /> comparaElementos
        </button>
        <span className="opsep" />
        <button className="opbtn ghost" onClick={doEjemplo} title="Cargar árbol de ejemplo">
          Ejemplo
        </button>
        <button className="opbtn ghost" onClick={doVaciar} title="Vaciar el árbol">
          Vaciar
        </button>
      </div>

      <main className="grid">
        <section className="left">
          <div className="treewrap">
            <TreeView frame={frame} />
          </div>

          <div className="desc">{frame.desc}</div>

          <div className="inorder">
            <ListTree size={14} />
            <span className="dim" style={{ fontSize: 12, marginRight: 4 }}>InOrder:</span>
            {orden.length === 0 ? <span className="dim" style={{ fontSize: 12 }}>— vacío —</span> : orden.map((v, i) => <span key={i} className="ochip">{v}</span>)}
          </div>

          <div className="legend">
            {LEGEND.map((l, i) => (
              <span key={i} className="legitem">
                <span className="dot" style={{ background: l.c.fill, borderColor: l.c.stroke }} />
                {l.t}
              </span>
            ))}
          </div>
        </section>

        <section className="right">
          <div className="paneltitle" style={{ marginBottom: 6 }}>
            <Code2 size={14} /> Código C++ — {op.title}
          </div>
          <CodePanel code={op.code} line={frame.line} />

          <div className="controls">
            <button className="btn" onClick={() => { setPlaying(false); setIdx(0); }} title="Reiniciar">
              <RotateCcw size={17} />
            </button>
            <button className="btn" onClick={() => { setPlaying(false); setIdx((i) => Math.max(i - 1, 0)); }} disabled={idx === 0} title="Paso anterior (←)">
              <ChevronLeft size={19} />
            </button>
            <button className="btn play" onClick={() => setPlaying((p) => (idx >= last ? p : !p))} disabled={idx >= last} title="Reproducir / Pausar (espacio)">
              {playing ? <Pause size={19} /> : <Play size={19} />}
            </button>
            <button className="btn" onClick={() => { setPlaying(false); setIdx((i) => Math.min(i + 1, last)); }} disabled={idx >= last} title="Siguiente paso (→)">
              <ChevronRight size={19} />
            </button>
            <span className="stepcount">Paso {idx + 1} / {frames.length}</span>
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

          <input type="range" min={0} max={last} value={idx} onChange={(e) => { setPlaying(false); setIdx(+e.target.value); }} className="slider" />

          <div className="panelbox">
            <div className="paneltitle"><Target size={14} /> Objetivo de la operación</div>
            {frame.target == null ? <span className="dim" style={{ fontSize: 12 }}>— sin valor objetivo —</span> : <span className="outchip">{frame.target}</span>}
          </div>

          <div className="panelbox">
            <div className="paneltitle"><Terminal size={14} /> Resultado</div>
            {frame.result == null ? (
              <span className="dim" style={{ fontSize: 12 }}>— aún sin resultado —</span>
            ) : (
              <span className={`reschip ${frame.result === false ? "bad" : frame.result === "duplicado" ? "warn" : "ok"}`}>
                {frame.result === true ? "true" : frame.result === false ? "false" : String(frame.result)}
              </span>
            )}
          </div>
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
.header { display: flex; align-items: center; gap: 12px; padding: 14px 22px; border-bottom: 1px solid #1e293b; }
.dim { color: #64748b; }
.opbar {
  display: flex; align-items: center; gap: 8px; flex-wrap: wrap;
  padding: 12px 22px; border-bottom: 1px solid #1e293b; background: #0d1626;
}
.numinput {
  width: 84px; background: #0f172a; border: 1px solid #334155; color: #e2e8f0;
  border-radius: 8px; padding: 8px 10px; font-size: 15px; font-weight: 700;
  font-family: ui-monospace, monospace;
}
.numinput:focus { outline: none; border-color: #0284c7; }
.opbtn {
  display: inline-flex; align-items: center; gap: 6px;
  border-radius: 8px; padding: 8px 13px; font-size: 13px; font-weight: 700;
  cursor: pointer; border: 1px solid; transition: all .15s; color: #e2e8f0;
}
.opbtn:disabled { opacity: 0.4; cursor: default; }
.opbtn.ins { background: #065f46; border-color: #059669; }
.opbtn.ins:hover:not(:disabled) { background: #047857; }
.opbtn.bus { background: #0c4a6e; border-color: #0284c7; }
.opbtn.bus:hover:not(:disabled) { background: #075985; }
.opbtn.eli { background: #7f1d1d; border-color: #b91c1c; }
.opbtn.eli:hover:not(:disabled) { background: #991b1b; }
.opbtn.alt { background: #1e293b; border-color: #475569; color: #cbd5e1; }
.opbtn.alt:hover { background: #334155; }
.opbtn.ghost { background: transparent; border-color: #334155; color: #94a3b8; font-weight: 600; }
.opbtn.ghost:hover { color: #e2e8f0; border-color: #475569; }
.opsep { width: 1px; height: 26px; background: #1e293b; margin: 0 2px; }
.grid {
  flex: 1; display: grid; grid-template-columns: minmax(0, 1.25fr) minmax(0, 1fr);
  gap: 18px; padding: 18px 22px; align-items: start;
}
@media (max-width: 980px) { .grid { grid-template-columns: 1fr; } }
.left { display: flex; flex-direction: column; gap: 12px; }
.treewrap { background: #0f172a; border: 1px solid #1e293b; border-radius: 14px; padding: 8px; min-height: 380px; display: flex; }
.desc {
  background: #082f49; border: 1px solid #0369a1; border-radius: 12px;
  padding: 12px 16px; font-size: 14.5px; line-height: 1.55; color: #bae6fd; min-height: 64px;
}
.inorder { display: flex; align-items: center; gap: 6px; flex-wrap: wrap; color: #7dd3fc; }
.ochip {
  font-family: ui-monospace, monospace; font-size: 12.5px; font-weight: 700;
  background: #0f172a; border: 1px solid #334155; color: #cbd5e1; border-radius: 6px; padding: 2px 8px;
}
.legend { display: flex; gap: 14px; flex-wrap: wrap; font-size: 12px; color: #94a3b8; }
.legitem { display: inline-flex; align-items: center; gap: 6px; }
.dot { width: 13px; height: 13px; border-radius: 50%; display: inline-block; border: 2px solid; }
.right { display: flex; flex-direction: column; gap: 12px; }
.codebox {
  background: #0f172a; border: 1px solid #1e293b; border-radius: 12px;
  padding: 10px 0; font-family: ui-monospace, SFMono-Regular, Menlo, monospace;
  font-size: 12.5px; line-height: 1.65; overflow: auto; max-height: 360px;
}
.codeline { display: flex; padding: 0 12px; color: #94a3b8; border-left: 3px solid transparent; }
.codeline.hl { background: #422006; color: #fef3c7; border-left-color: #f59e0b; }
.lnum { width: 30px; flex-shrink: 0; text-align: right; margin-right: 14px; color: #475569; user-select: none; }
.codeline.hl .lnum { color: #b45309; }
.controls { display: flex; align-items: center; gap: 8px; flex-wrap: wrap; }
.btn {
  background: #1e293b; border: 1px solid #334155; color: #e2e8f0; border-radius: 9px;
  width: 40px; height: 38px; cursor: pointer; display: inline-flex; align-items: center; justify-content: center; transition: all .15s;
}
.btn:hover:not(:disabled) { background: #334155; }
.btn:disabled { opacity: 0.35; cursor: default; }
.btn.play { background: #065f46; border-color: #059669; }
.btn.play:hover:not(:disabled) { background: #047857; }
.stepcount { font-size: 13px; color: #94a3b8; font-weight: 600; margin-left: 4px; }
.speed { display: inline-flex; align-items: center; gap: 5px; margin-left: auto; color: #64748b; }
.speed select { background: #1e293b; color: #e2e8f0; border: 1px solid #334155; border-radius: 7px; padding: 4px 6px; font-size: 12px; }
.slider { width: 100%; accent-color: #0ea5e9; cursor: pointer; }
.panelbox { background: #0f172a; border: 1px solid #1e293b; border-radius: 12px; padding: 10px 14px; }
.paneltitle {
  display: flex; align-items: center; gap: 7px; font-size: 12px; font-weight: 700;
  text-transform: uppercase; letter-spacing: 0.06em; color: #7dd3fc; margin-bottom: 7px;
}
.outchip {
  font-family: ui-monospace, monospace; font-size: 13px; font-weight: 700;
  background: #0c4a6e; border: 1px solid #0284c7; color: #7dd3fc; border-radius: 7px; padding: 3px 12px;
}
.reschip { font-family: ui-monospace, monospace; font-size: 14px; font-weight: 800; border-radius: 7px; padding: 3px 14px; }
.reschip.ok { background: #14532d; border: 1px solid #22c55e; color: #bbf7d0; }
.reschip.bad { background: #7f1d1d; border: 1px solid #ef4444; color: #fecaca; }
.reschip.warn { background: #422006; border: 1px solid #f59e0b; color: #fde68a; }
`;
