#ifndef FE_H
#define FE_H

#include "main.h"
#define MAX_FILA 10

typedef struct {
    Download info[MAX_FILA];
    int ini;
    int fim;
    int tam;
} Fila;

//funções da fila estática
void cria_fila(Fila *f);
int f_vazia(Fila *f);
int f_cheia(Fila *f);
int push_f(Fila *f, Download item);
int pop_f(Fila *f, Download *item);
int f_tam(Fila *f);
void free_f(Fila *f);

#endif
