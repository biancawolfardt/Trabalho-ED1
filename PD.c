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
    return p->tam == MAX_HISTORICO;
}

//função para adicionar na pilha
int push_p(Pilha *p, URL url){
    if (p_cheia(p)){
        printf("Pilha Cheia. \n");
        return 0; //Pilha cheia
    }
    Nodo *novo = (Nodo *)malloc(sizeof(Nodo));
    if (novo == NULL) {
        printf("Erro de Alocação. \n");
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
        printf("Pilha Vazia. \n");
        return 0; //Pilha vazia
    }

    Nodo *aux = p->topo;
    strcpy(url, aux->url);

    p->topo = aux->prox;
    free(aux);

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
        URL temp_url;
        while (!p_vazia(p)) {
            pop_p(p);
        }
    }
}
