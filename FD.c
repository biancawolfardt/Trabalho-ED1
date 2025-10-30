#include "FD.h"
#include <stdio.h>
#include <stdlib.h>

//Fun��es Fila Din�mica

//fun��o que cria a fila
void cria_fila(Fila *f){
    f->ini = f->fim;
    f->fim = NULL;
    f->tam = 0;
}

//fun��o que verifica se a fila est� vazia
int f_vazia(Fila *f){
    if(f->ini == NULL)
        return 1;
    else
        return 0;
}

//fun��o que verifica se a fila est� cheia
int f_cheia(Fila *f){
    return (f->tam >= MAX_FILA);
}

//fun��o que adiciona na fila
int push_f(Fila *f, Download item){
    if (f_cheia(f)){
        return;
    }
    Nodo *novo = (Nodo *)malloc(sizeof(Nodo));
    novo->info = item;
    novo->prox = NULL;
    if (f->fim != NULL){
        f->fim->prox = novo;
        f->fim = novo;
    }
    if (f_vazia(f)){
        f->ini = novo;
    }
    else{
        f->fim->prox = novo;
    }
    f->fim = novo;
    f->tam++;
    return 1;
}

//fun��o que retira da fila
int pop_f(Fila *f, Download *item){
    if (f_vazia(f)){
        return 0;
    }
    Nodo *aux = f->ini;
    *item = aux->info;
    if (f->ini == NULL){
        f->fim = aux->prox;
        f->fim = NULL;
    }
    else
        free(f->ini);
    f->tam--;
    free(aux);
    return 1;
}

//fun��o que retorna o tamanho atual da fila
int f_tam(Fila *f){
    return f->tam;
}

//fun��o que libera a fila
void free_f(Fila *f){
    Download temp;
    while (!f_vazia(f))
        pop_f(f, &temp);
}
