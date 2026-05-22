#include <iostream>

#include "BibliotecaColas/Cola.h"
#include "BibliotecaColas/FuncionesCola.h"
using namespace std;

/*
 * Estrategia de solucion:
 * Se simulan los eventos de llegada de los 6 clientes mediante un bucle for.
 * En cada iteracion (que representa un salto de 15 segundos), el sistema primero
 * revisa si el cajero se libero antes de esta nueva llegada. Si es asi, desencola
 * y atiende a los clientes en espera, sumando 20s por atencion.
 * Si un VIP espero mas de 30s (cajeroLibreEn - tiempoLlegada > 30), se descarta
 * usando un simple if-else. Finalmente, el nuevo cliente ingresa a la cola.
 */
int main() {
    Cola colaAtencion;
    construirCola(colaAtencion);

    int cajeroLibreEn = 0;
    int vipsAtendidos = 0;
    int vipsAbandonaron = 0;

    // 1. Fase de llegadas (Procesamos a los 6 clientes)
    for (int i = 1; i <= 6; i++) {
        int tiempoLlegada = i * 15; // Llegan en el seg 15, 30, 45, 60, 75, 90
        char tipo = (i % 2 == 0) ? 'V' : 'N'; // Clientes pares son VIP

        // Antes de que el nuevo cliente entre, el cajero despacha a los que pueda
        // de la cola (si es que su tiempo de atencion termina antes de esta llegada)
        while (!esColaVacia(colaAtencion) && cajeroLibreEn <= tiempoLlegada) {
            ElementoCola clienteActual = desencolar(colaAtencion);

            if (clienteActual.tipoCliente == 'V' && (cajeroLibreEn - clienteActual.tiempoLlegada) > 30) {
                // El VIP espero demasiado, abandona y el cajero no gasta tiempo
                vipsAbandonaron++;
            } else {
                // Atencion exitosa
                cajeroLibreEn += 20; // El proceso dura 20 segundos
                if (clienteActual.tipoCliente == 'V') {
                    vipsAtendidos++;
                }
            }
        }

        // Si el cajero estaba totalmente desocupado (ej. al inicio),
        // avanzamos su reloj al momento exacto en que llega este nuevo cliente
        if (cajeroLibreEn < tiempoLlegada) {
            cajeroLibreEn = tiempoLlegada;
        }

        // Encolamos al cliente que acaba de llegar
        ElementoCola nuevoCliente;
        nuevoCliente.idCliente = i;
        nuevoCliente.tipoCliente = tipo;
        nuevoCliente.tiempoLlegada = tiempoLlegada;
        encolar(colaAtencion, nuevoCliente);
    }

    // 2. Fase final: El banco cierra sus puertas (ya no llegan mas clientes),
    // pero el cajero debe terminar de atender a los que quedaron en la cola.
    while (!esColaVacia(colaAtencion)) {
        ElementoCola clienteActual = desencolar(colaAtencion);

        if (clienteActual.tipoCliente == 'V' && (cajeroLibreEn - clienteActual.tiempoLlegada) > 30) {
            vipsAbandonaron++;
        } else {
            cajeroLibreEn += 20;
            if (clienteActual.tipoCliente == 'V') {
                vipsAtendidos++;
            }
        }
    }

    // 3. Imprimir el cuadro de resultados exacto como pide el examen
    cout << "RESULTADOS DE LA SIMULACIÓN DEL DESPACHO DE ENTRADAS\n\n";
    cout << "Clientes VIP atendidos\tClientes VIP no atendidos\n";
    cout << "\t" << vipsAtendidos << "\t\t\t" << vipsAbandonaron << "\n";

    return 0;
}
