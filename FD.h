#ifndef FD_H
#define FD_H

#include "main.h"

typedef struct FNodo{
    Download info;
    struct FNodo *prox;
} FNodo;

typedef struct {
    FNodo *ini;
    FNodo *fim;
    int tam;
} Fila;

//funções da fila dinâmica
void cria_fila(Fila *f);
int f_vazia(Fila *f);
int f_cheia(Fila *f);
int push_f(Fila *f, Download item);
int pop_f(Fila *f, Download *item);
int f_tam(Fila *f);
void free_f(Fila*f);

#endif
