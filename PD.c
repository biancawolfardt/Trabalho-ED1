#include "PD.h"
#include <stdio.h>
#include <stdlib.h>

//Funções Pilha Dinâmica

//função para criar uma pilha
void cria_pilha(Pilha *p){
    p->topo = NULL;
    p->tam = 0;
}

//função que verifica se a pilha está vazia
int p_vazia(Pilha *p){
    if(p->topo == NULL)
        return 1;
    else
        return 0;
}

//função que verifica se a pilha está cheia
int p_cheia(Pilha *p){
    //o limite é dado pelo tamanho
    if(p->tam == MAX_HISTORICO)
        return 1;
    else
        return 0;
}

//função para adicionar na pilha
int push_p(Pilha *p, URL url){
    if (p_cheia(p)){
        return 0; //Pilha cheia
    }
    PNodo *novo = (PNodo *)malloc(sizeof(PNodo));
    if (novo == NULL) {
        return 0; //Erro de alocação
    }
    else{
        strcpy(novo->url, url);
        novo->prox = p->topo;
        p->topo = novo;
        p->tam++;
        return 1;
    }
}

//função que retira um elemento da pilha
int pop_p(Pilha *p, URL url){
    if (p_vazia(p)) {
        return 0; //Pilha vazia
    }
    PNodo *aux = p->topo;
    strcpy(url, aux->url);

    p->topo = aux->prox;
    free(aux);

    p->tam--;
    return 1;
}

//função que remove o primeiro elemento da pilha
int remove_base(Pilha *p) {
    if (p_vazia(p)) {
        return 0;
    }
    if (p->tam == 1) {  //se só tem um elemento na pilha
        free(p->topo);
        p->topo = NULL;
        p->tam = 0;
        return 1;
    }
    PNodo *atual = p->topo;
    while (atual->prox->prox != NULL) { //percorre até o nodo que aponta para a base
        atual = atual->prox;
    }
    free(atual->prox); //libera o último nodo
    atual->prox = NULL; //o penúltimo se torna o último
    p->tam--;
    return 1;
}

//função que retorna o tamanho da pilha
int p_tam(Pilha *p){
    return p->tam;
}

//função para liberar a pilha
void free_p(Pilha *p){
    if(p != NULL){
        URL temp_url; //variável temporária para receber o valor
        while (!p_vazia(p)) {
            pop_p(p, temp_url);
        }
    }
}
