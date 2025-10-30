#ifndef PD_H#ifndef PD_H
#define PD_H

#include "main.h"

typedef struct PNodo {
    URL url;
    struct PNodo *prox;
} PNodo;

typedef struct {
    PNodo *topo;
    int tam;
} Pilha;

void cria_pilha(Pilha *p);
int p_vazia(Pilha *p);
int p_cheia(Pilha *p);
int push_p(Pilha *p, URL url);
int pop_p(Pilha *p, URL url);
int remove_base(Pilha *p);
int p_tam(Pilha *p);
void free_p(Pilha *p);

#endif


