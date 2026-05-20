//
// Created by Miguel Bazan on 21/04/26.
//

#ifndef LISTASFUNCIONES_LISTAFUNCIONES_H
#define LISTASFUNCIONES_LISTAFUNCIONES_H
#include "lista.h"

void construirLista(Lista &listaTAD);
bool esListaVacia(const Lista &listaTAD);
void insertarInicio(Lista &listaTAD,const ElementoLista &elemento);
void insertarFinal(Lista &listaTAD, const ElementoLista &elemento);
void insertarEnOrden(Lista &listaTAD,const ElementoLista &elemento);
void eliminarNodo(Lista &listaTAD,const ElementoLista &elemento);
void eliminarLista(Lista &listaTAD);

void imprimirLista(const Lista &listaTAD);



#endif //LISTASFUNCIONES_LISTAFUNCIONES_H
