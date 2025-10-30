#ifndef PE_H
#define PE_H

#include "main.h"

typedef struct {
    URL info[MAX_HISTORICO];
    int topo; //posição do topo da pilha, inicialmente -1
} Pilha;

//funções da pilha dinâmica
void cria_pilha(Pilha *p);
int p_vazia(Pilha *p);
int p_cheia(Pilha *p);
int push_p(Pilha *p, URL url);
int pop_p(Pilha *p, URL url);
int p_tam(Pilha *p);
void free_p(Pilha *p);

#endif;

