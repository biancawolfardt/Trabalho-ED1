#include "FD.h"
#include <stdio.h>
#include <stdlib.h>

//Funções Fila Dinâmica

//função que cria a fila
void cria_fila(Fila *f){
    f->ini = NULL;
    f->fim = NULL;
    f->tam = 0;
}

//função que verifica se a fila está vazia
int f_vazia(Fila *f){
    if(f->ini == NULL)
        return 1;
    else
        return 0;
}

//função que verifica se a fila está cheia
int f_cheia(Fila *f){
    if(f->tam >= MAX_FILA)
        return 1;
    else
        return 0;
}

//função que adiciona na fila
int push_f(Fila *f, Download item){
    if (f_cheia(f)){
        return 0;
    }
    Nodo *novo = (Nodo *)malloc(sizeof(Nodo));
    if(novo == NULL)
        return 0;
    novo->info = item;
    novo->prox = NULL;
    if (f_vazia(f)){ //se a fila estiver vazia
        f->ini = novo;
    }
    else (f_vazia(f)){ //se a fila não estiver vazia
        f->fim->prox = novo;
    }

    f->fim = novo; //o novo nodo é o fim agora
    f->tam++;
    return 1;
}

//função que retira da fila
int pop_f(Fila *f, Download *item){
    if (f_vazia(f)){
        return 0;
    }
    Nodo *aux = f->ini; //salva o nodo a ser removido
    *item = aux->info; //salva os dados do nodo
    f->ini = aux->prox; //avança o ponteiro pro próximo nodo
    if (f->ini == NULL){
        f->fim = NULL;
    }
    f->tam--;
    free(aux);
    return 1;
}

//função que retorna o tamanho atual da fila
int f_tam(Fila *f){
    return f->tam;
}

//função que libera a fila
void free_f(Fila *f){
    Download temp;
    while (!f_vazia(f))
        pop_f(f, &temp); //libera cada nodo individualmente
}

