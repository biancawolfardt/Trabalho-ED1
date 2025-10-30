#ifndef PD_H
#define PD_H

#include "main.h"

typedef struct Nodo {
    URL url;
    struct Nodo *prox;
} Nodo;

typedef struct {
    Nodo *topo;
    int tam;
} Pilha;

void cria_pilha(Pilha *p);
int p_vazia(Pilha *p);
int p_cheia(Pilha *p);
int push_p(Pilha *p, URL url);
int pop_p(Pilha *p, URL url);
int p_tam(Pilha *p);
void free_p(Pilha *p);

#endif

