#include "FE.h"
#include <stdio.h>
#include <stdlib.h>

//Fun��es Fila Est�tica

//fun��o para criar uma fila
void cria_fila(Fila *f){
    f->ini = f->fim = 0;
    f->tam = 0;
}

//fun��o que verifica se a fila est� vazia
int f_vazia(Fila *f){
        if(f->tam == 0)
        return 1;
    else
        return 0;
}

//fun��o que verifica se a fila est� cheia
int f_cheia(Fila *f){
    return f->tam == MAX_FILA;
}

//fun��o que insere na fila
int push_f(Fila *f, Download item){
    if (f_cheia(f))
        return 0; //fila cheia
    if(!f_cheia(f)){ //se n�o estiver cheia
        f->info[f->fim] = item;
        f->fim = (f->fim + 1) % MAX_FILA;
        f->tam++;
        return 1;
    }
}

//fun��o que remove da fila
int pop_f(Fila *f, Download *item){
    if (f_vazia(f)){
        printf("Fila Vazia. \n");
        return 0; //fila vazia
    }
    else{
        *item = f->info[f->ini]; //salva o primeiro elemento da fila na vari�vel item
        f->ini = (f->ini + 1) % MAX_FILA; //volta ao primeiro elemento da fila e avan�a
        f->tam--;
        return 1;
    }
}

//fun��o que retorna o tamanho da fila
int f_tam(Fila *f){
    return f->tam;
}

//fun��o que libera a fila
void free_f(Fila *f){

}
