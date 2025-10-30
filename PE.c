#include "PE.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Fun��es Pilha Est�tica

//fun��o para criar uma pilha
void cria_pilha(Pilha *p) {
    p->topo = -1;
}

//fun��o que verifica se a pilha est� vazia
int p_vazia(Pilha *p){
    return p->topo == -1;
}

//fun��o que verifica se a pilha est� cheia
int p_cheia(Pilha *p){
    return p->topo == MAX_HISTORICO - 1;
}

//fun��o que insere um elemento na pilha
int push_p(Pilha *p, URL url){
    if (p_cheia(p)){
        return 0; //pilha cheia
    }
    else{
        p->topo++;
        strcpy(p->info[p->topo], url);
        return 1;
    }
}

//fun��o que remove um elemento da pilha
int pop_p(Pilha *p, URL url){
    if(p_vazia(p)){
        return 0; //pilha vazia
    }
    else{
        strcpy(url, p->info[p->topo]);
        p->topo--;
        return 1;
    }
}

//fun��o que retorna o tamanho da pilha
int p_tam(Pilha *p){
    return p-> topo + 1;
}

//fun��o que libera a pilha
void free_p(Pilha *p){

}
