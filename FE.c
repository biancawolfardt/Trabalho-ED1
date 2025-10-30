#include "FE.h"
#include <stdio.h>
#include <stdlib.h>

//Funções Fila Estática

//função para criar uma fila
void cria_fila(Fila *f){
    f->ini = f->fim = 0;
    f->tam = 0;
}

//função que verifica se a fila está vazia
int f_vazia(Fila *f){
    if(f->tam == 0)
        return 1;
    else
        return 0;
}

//função que verifica se a fila está cheia
int f_cheia(Fila *f){
    if(f->tam == MAX_FILA)
        return 1;
    else
        return 0;
}

//função que insere na fila
int push_f(Fila *f, Download item){
    if (f_cheia(f))
        return 0; //fila cheia
    else{ //se não estiver cheia
        f->info[f->fim] = item;
        f->fim = (f->fim + 1) % MAX_FILA; //volta quando chega no último indíce ou avança se não
        f->tam++;
        return 1;
    }
}

//função que remove da fila
int pop_f(Fila *f, Download *item){
    if (f_vazia(f)){
        printf("Fila Vazia. \n");
        return 0; //fila vazia
    }
    else{
        *item = f->info[f->ini]; //salva o primeiro elemento da fila na variável item
        f->ini = (f->ini + 1) % MAX_FILA; //volta ao primeiro elemento da fila e avança
        f->tam--;
        return 1;
    }
}

//função que retorna o tamanho da fila
int f_tam(Fila *f){
    return f->tam;
}

//função que libera a fila
void free_f(Fila *f){
    //não faz nada já que a fila é alocada estaticamente
}
