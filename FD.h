#ifndef FD_H
#define FD_H

#include "main.h"

typedef struct Nodo {
    Download info;
    struct Nodo *prox;
} Nodo;

typedef struct {
    Nodo *ini;
    Nodo *fim;
    int tam;
} Fila;

//fun��es da fila din�mica
void cria_fila(Fila *f);
int f_vazia(Fila *f);
int f_cheia(Fila *f);
int push_f(Fila *f, Download item);
int pop_f(Fila *f, Download *item);
int f_tam(Fila *f);
void free_f(Fila*f);

#endif
